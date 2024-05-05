/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:07 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/05 14:58:21 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file(t_mini *mini, t_cmd **cmd, t_token **token);
static int	check_cmd(t_mini *mini, t_cmd **cmd, t_token **token, int *arg_flag);
static int	init_cmd(t_mini *mini, t_cmd **cmd, int skip);

int	parser(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		arg_flag;
	int		skip;

	arg_flag = 0;
	skip = 0;
	token = mini->h_token;
	init_cmd(mini, &cmd, skip);
	get_sig()->status = 0;
	while (token)
	{
		skip = 0;
		if (token && (token->type == INPUT || token->type == HEREDOC
				|| token->type == APPEND || token->type == TRUNC))
			skip += check_file(mini, &cmd, &token);
		if (token && token->type == STR)
			skip += check_cmd(mini, &cmd, &token, &arg_flag);
		if (token && token->type == PIPE)
		{
			if (cmd)
				new_cmd(&mini, &cmd, &arg_flag);
			init_cmd(mini, &cmd, skip);
			get_sig()->status = 0;
			arg_flag = 0;
			token = token->next;
		}
	}
	if (cmd)
		new_cmd(&mini, &cmd, &arg_flag);
	return (get_sig()->status);
}

static int	check_file(t_mini *mini, t_cmd **cmd, t_token **token)
{
	int	fd;

	fd = -1;
	if ((*token)->type == INPUT || (*token)->type == HEREDOC)
	{
		if (access((*token)->next->str, R_OK) == -1)
			return (parser_err(mini, (*token)->next->str, errno), cmd_skip(mini, cmd, token), errno);
		else
		{
			if ((*cmd)->in)
				free((*cmd)->in);
			(*cmd)->in = ft_strdup((*token)->next->str);
			if (!(*cmd)->in)
				return (free_cmd(cmd), error_manager(mini, MALLOC, NULL, NULL), ERROR);
		}
	}
	else if ((*token)->type == APPEND || (*token)->type == TRUNC)
	{
		if ((*token)->type == APPEND)
			fd = open((*token)->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if ((*token)->type == TRUNC)
			fd = open((*token)->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
			close(fd);
		if (fd < 0 || access((*token)->next->str, W_OK) == -1)
			return (parser_err(mini, (*token)->next->str, errno), cmd_skip(mini, cmd, token), errno);
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
				return (free_cmd(cmd), error_manager(mini, MALLOC, NULL, NULL), ERROR);
		}
	}
	(*token) = (*token)->next->next;
	return (SUCCESS);
}

static int	check_cmd(t_mini *mini, t_cmd **cmd, t_token **token, int *arg_flag)
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
		path_finder(mini, cmd, (*token)->str); //to protect
	else if (ft_strchr((*token)->str, '/'))
		(*cmd)->args = add_args(mini, cmd, (*token)->str);
	if ((*cmd)->args && (*cmd)->args[0])
		stat((*cmd)->args[0], &st);
	if ((*cmd)->builtin != NONE || ((*cmd)->args && access((*cmd)->args[0], X_OK) == 0 && !S_ISDIR(st.st_mode)))
		(*arg_flag)++;
	else if ((*cmd)->args && access((*cmd)->args[0], F_OK) == -1)
		return (parser_err(mini, (*token)->str, MISSING), cmd_skip(mini, cmd, token), ERROR);
	else if ((*cmd)->args && S_ISDIR(st.st_mode))
		return (parser_err(mini, (*token)->str, DIRECTORY), cmd_skip(mini, cmd, token), ERROR);
	else if ((*cmd)->args && (!(st.st_mode & S_IXUSR) || 
		(st.st_uid == 0 && !(st.st_mode & S_IXOTH)) || S_ISDIR(st.st_mode)))
		{
			parser_err(mini, (*token)->str, errno);
			get_sig()->status = 126;
			return (cmd_skip(mini, cmd, token), ERROR);
		}
	else
		return (parser_err(mini, (*token)->str, EXE), cmd_skip(mini, cmd, token), ERROR);
	(*token) = (*token)->next;
	return (SUCCESS);
}

static int	init_cmd(t_mini *mini, t_cmd **cmd, int skip)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (error_manager(mini, MALLOC, NULL, NULL));
	(*cmd)->args = NULL;
	if (skip == 0)
		(*cmd)->in = NULL;
	else
	{
		(*cmd)->in = ft_strdup("/dev/null");
		if (!(*cmd)->in)
			return (free((*cmd)), error_manager(mini, MALLOC, NULL, NULL));
	}
	(*cmd)->out = NULL;
	(*cmd)->fd[0] = -1;
	(*cmd)->fd[1] = -1;
	(*cmd)->pid = -1;
	(*cmd)->append = 0;
	(*cmd)->builtin = NONE;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
	return (0);
}
