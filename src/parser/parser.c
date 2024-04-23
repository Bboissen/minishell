/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbsn <bbsn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:07 by bbsn              #+#    #+#             */
/*   Updated: 2024/04/23 10:25:30 by bbsn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_file(t_mini *mini, t_cmd **cmd, t_token **token);
static void	check_cmd(t_mini *mini, t_cmd **cmd, t_token **token, int *arg_flag);
static int	init_cmd(t_mini *mini, t_cmd **cmd);

void	parser(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		arg_flag;

	arg_flag = 0;
	token = mini->h_token;
	init_cmd(mini, &cmd);
	while (token)
	{
		if (token && (token->type == INPUT || token->type == HEREDOC
			|| token->type == APPEND || token->type == TRUNC))
			check_file(mini, &cmd, &token);
		if (token && token->type == STR)
			check_cmd(mini, &cmd, &token, &arg_flag);
		if (token && token->type == PIPE)
		{
			if (cmd)
				new_cmd(&mini, &cmd, &arg_flag);
			init_cmd(mini, &cmd);
			arg_flag = 0;
			token = token->next;
		}
	}
	if (cmd)
		new_cmd(&mini, &cmd, &arg_flag);
}

static void	check_file(t_mini *mini, t_cmd **cmd, t_token **token)
{
	int	fd;
	
	fd = -1;
	if ((*token)->type == INPUT || (*token)->type == HEREDOC)
	{
		if (access((*token)->next->str, R_OK) == -1)
			return (cmd_skip(mini, cmd, token));
		else
			(*cmd)->in = ft_strdup((*token)->next->str);
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
			return (cmd_skip(mini, cmd, token));
		else
			(*cmd)->out = ft_strdup((*token)->next->str);
	}
	(*token) = (*token)->next->next;
}

static void	check_cmd(t_mini *mini, t_cmd **cmd, t_token **token, int *arg_flag)
{
	if (*arg_flag)
	{
		if ((*cmd)->builtin == EXPORT)
		{
			return (cmd_skip(mini, cmd, token));
		}
		(*cmd)->args = add_args(cmd, (*token)->str);
		(*token) = (*token)->next;
		return ;
	}
	(*cmd)->builtin = check_blt(cmd, (*token)->str, arg_flag);
	if ((*cmd)->builtin == NONE && !ft_strchr((*token)->str, '/'))
		path_finder(mini, cmd, (*token)->str);
	else if (ft_strchr((*token)->str, '/'))
		(*cmd)->args = add_args(cmd, (*token)->str);
	if ((*cmd)->builtin != NONE || ((*cmd)->args && access((*cmd)->args[0], X_OK) == 0))
		(*arg_flag)++;
	else
		return (parser_err(mini, (*token)->str, EXE, 0)); //WIP parser error and then skip
	(*token) = (*token)->next;
}

static int	init_cmd(t_mini *mini, t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (error_manager(mini, MALLOC, NULL, NULL)); //protected
	(*cmd)->args = NULL;
	(*cmd)->in = NULL;
	(*cmd)->out = NULL;
	(*cmd)->fd[0] = -1;
	(*cmd)->fd[1] = -1;
	(*cmd)->pid = -1;
	(*cmd)->builtin = NONE;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
	return (0);
}
