/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:39:36 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/06 17:15:03 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	check_blt(t_cmd **cmd, char *str, int *arg_flag);
static int			check_write(t_mini *mini, t_cmd **cmd, t_token **token,
						int fd);
static int			check_access(t_mini *mini, t_cmd **cmd, t_token **token,
						struct stat st);

/**
 * @brief Checks if a file can be accessed.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to be checked.
 * @param token The current token.
 * @return {int} - Returns SUCCESS if the file can be accessed,
 * otherwise returns ERROR.
 */
int	check_file(t_mini *mini, t_cmd **cmd, t_token **token)
{
	int	fd;

	fd = -1;
	if ((*token)->type == INPUT || (*token)->type == HEREDOC)
	{
		if (access((*token)->next->str, R_OK) == -1)
			return (cmd_skip(mini, cmd, token, errno), ERROR);
		else
		{
			if ((*cmd)->in)
				free((*cmd)->in);
			(*cmd)->in = ft_strdup((*token)->next->str);
			if (!(*cmd)->in)
			{
				free_cmd(cmd);
				error_manager(mini, MALLOC, NULL, NULL);
			}
		}
	}
	else if ((*token)->type == APPEND || (*token)->type == TRUNC)
		if (check_write(mini, cmd, token, fd) == ERROR)
			return (ERROR);
	(*token) = (*token)->next->next;
	return (SUCCESS);
}

/**
 * @brief Checks if a file can be written to.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to be checked.
 * @param token The current token.
 * @param fd The file descriptor.
 * @return {int} - Returns SUCCESS if the file can be written to,
 * otherwise returns ERROR.
 */
static int	check_write(t_mini *mini, t_cmd **cmd, t_token **token, int fd)
{
	if ((*token)->type == APPEND)
		fd = open((*token)->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if ((*token)->type == TRUNC)
		fd = open((*token)->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd >= 0)
		close(fd);
	if (fd < 0 || access((*token)->next->str, W_OK) == -1)
		return (cmd_skip(mini, cmd, token, errno), ERROR);
	else
	{
		if ((*token)->type == APPEND)
			(*cmd)->append = 1;
		else
			(*cmd)->append = 0;
		if ((*cmd)->out)
			free((*cmd)->out);
		(*cmd)->out = ft_strdup((*token)->next->str);
		if (!(*cmd)->out)
		{
			free_cmd(cmd);
			error_manager(mini, MALLOC, NULL, NULL);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Checks a command in the shell.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to be checked.
 * @param token The current token.
 * @param arg_flag Pointer to the argument flag.
 * @return {int} - Returns SUCCESS if the command is valid,
 * otherwise returns ERROR.
 */
int	check_cmd(t_mini *mini, t_cmd **cmd, t_token **token,
				int *arg_flag)
{
	struct stat	st;

	if (*arg_flag)
	{
		(*cmd)->args = add_args(mini, cmd, (*token)->str);
		(*token) = (*token)->next;
		return (SUCCESS);
	}
	(*cmd)->builtin = check_blt(cmd, (*token)->str, arg_flag);
	if ((*cmd)->builtin == NONE && !ft_strchr((*token)->str, '/'))
		path_finder(mini, cmd, (*token)->str);
	else if (ft_strchr((*token)->str, '/'))
		(*cmd)->args = add_args(mini, cmd, (*token)->str);
	if ((*cmd)->args && (*cmd)->args[0])
		stat((*cmd)->args[0], &st);
	if ((*cmd)->builtin != NONE || ((*cmd)->args
			&& access((*cmd)->args[0], X_OK) == 0 && !S_ISDIR(st.st_mode)))
		(*arg_flag)++;
	else
		return (check_access(mini, cmd, token, st));
	(*token) = (*token)->next;
	return (SUCCESS);
}

/**
 * @brief Checks if a command is a built-in command.
 * 
 * @param cmd The command to be checked.
 * @param str The string representation of the command.
 * @param arg_flag Pointer to the argument flag.
 * @return {t_builtin} - Returns the type of the built-in command if it
 * is a built-in command, otherwise returns NONE.
 */
static t_builtin	check_blt(t_cmd **cmd, char *str, int *arg_flag)
{
	if (ft_strcmp(str, "echo") == 0)
		(*cmd)->builtin = ECHO;
	else if (ft_strcmp(str, "cd") == 0)
		(*cmd)->builtin = CD;
	else if (ft_strcmp(str, "pwd") == 0)
		(*cmd)->builtin = PWD;
	else if (ft_strcmp(str, "export") == 0)
		(*cmd)->builtin = EXPORT;
	else if (ft_strcmp(str, "unset") == 0)
		(*cmd)->builtin = UNSET;
	else if (ft_strcmp(str, "env") == 0)
		(*cmd)->builtin = ENV;
	else if (ft_strcmp(str, "exit") == 0)
		(*cmd)->builtin = EXIT;
	else
		(*cmd)->builtin = NONE;
	if ((*cmd)->builtin != NONE)
		*arg_flag = 1;
	return ((*cmd)->builtin);
}

/**
 * @brief Checks if a command can be accessed.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to be checked.
 * @param token The current token.
 * @param st The stat structure of the command.
 * @return {int} - Returns SUCCESS if the command can be accessed,
 * otherwise returns ERROR.
 */
static int	check_access(t_mini *mini, t_cmd **cmd, t_token **token,
			struct stat st)
{
	if ((*cmd)->args && access((*cmd)->args[0], F_OK) == -1)
		return (cmd_skip(mini, cmd, token, MISSING), ERROR);
	else if ((*cmd)->args && S_ISDIR(st.st_mode))
		return (cmd_skip(mini, cmd, token, DIRECTORY), ERROR);
	else if ((*cmd)->args && (!(st.st_mode & S_IXUSR) || (st.st_uid == 0
				&& !(st.st_mode & S_IXOTH)) || S_ISDIR(st.st_mode)))
	{
		get_sig()->status = 126;
		return (cmd_skip(mini, cmd, token, errno), ERROR);
	}
	else
		return (cmd_skip(mini, cmd, token, EXE), ERROR);
}
