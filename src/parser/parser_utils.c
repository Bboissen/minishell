/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:59 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/06 17:53:50 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	args_cleaner( t_mini *mini, t_cmd **cmd, char **new_cmd);

/**
 * @brief Adds arguments to a command.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to which the arguments will be added.
 * @param str The argument to be added.
 * @return {char **} - Returns a new array of arguments.
 */
char	**add_args(t_mini *mini, t_cmd **cmd, char *str)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	while ((*cmd)->args && (*cmd)->args[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	if (!new_cmd)
		return (free_cmd(cmd), error_manager(mini, MALLOC, NULL, NULL), NULL);
	j = 0;
	while (j < i)
	{
		new_cmd[j] = ft_strdup((*cmd)->args[j]);
		if (!new_cmd[j])
			args_cleaner(mini, cmd, new_cmd);
		j++;
	}
	new_cmd[j] = ft_strdup(str);
	if (!new_cmd[j])
		args_cleaner(mini, cmd, new_cmd);
	new_cmd[j + 1] = NULL;
	if ((*cmd)->args)
		free_tab((*cmd)->args);
	return (new_cmd);
}

/**
 * @brief Cleans up arguments and a command.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to be cleaned up.
 * @param new_cmd The new array of arguments to be cleaned up.
 */
static void	args_cleaner( t_mini *mini, t_cmd **cmd, char **new_cmd)
{
	free_tab(new_cmd);
	free_cmd(cmd);
	error_manager(mini, MALLOC, NULL, NULL);
}

/**
 * @brief Skips a command during the parsing.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to be skipped.
 * @param token The current token.
 * @param err The error code.
 */
void	cmd_skip(t_mini *mini, t_cmd **cmd, t_token **token, int err)
{
	if ((*token)->type == INPUT || (*token)->type == HEREDOC
		|| (*token)->type == APPEND || (*token)->type == TRUNC)
		parser_err(mini, (*token)->next->str, errno);
	else
		parser_err(mini, (*token)->str, err);
	while ((*token) && (*token)->type != PIPE)
		(*token) = (*token)->next;
	free_cmd(cmd);
	if (mini->cmd)
	{
		if (mini->cmd->out)
			free(mini->cmd->out);
		mini->cmd->out = ft_strdup("/dev/null");
		if (mini->cmd->out == NULL)
			error_manager(mini, MALLOC, NULL, NULL);
	}
}

/**
 * @brief Adds a new command to the list.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The new command to be added.
 * @param arg_flag Pointer to the argument flag.
 */
void	new_cmd(t_mini **mini, t_cmd **cmd, int *arg_flag)
{
	if (!(*mini)->cmd)
	{
		(*mini)->h_cmd = *cmd;
		(*mini)->cmd = (*mini)->h_cmd;
	}
	else
	{
		(*mini)->cmd->next = *cmd;
		(*cmd)->prev = (*mini)->cmd;
		(*mini)->cmd = (*mini)->cmd->next;
	}
	*arg_flag = 0;
}

/**
 * @brief Checks if a token type is a file.
 * 
 * @param type The type of the token.
 * @return {int} - Returns FALSE if the token type is
 * INPUT, HEREDOC, APPEND, or TRUNC, otherwise returns TRUE.
 */
int	is_file(int type)
{
	if (type == INPUT || type == HEREDOC
		|| type == APPEND || type == TRUNC)
		return (TRUE);
	return (FALSE);
}
