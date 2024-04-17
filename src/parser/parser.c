/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:07 by bbsn              #+#    #+#             */
/*   Updated: 2024/04/17 15:50:31 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_file(t_mini *mini, t_cmd **cmd, t_token **token);
static void	check_cmd(t_mini *mini, t_cmd **cmd, t_token **token, int *arg_flag);
static void	init_cmd(t_cmd **cmd, int *pipe, t_mini *mini, t_token **token);

void	parser(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		arg_flag;
	int		pipe;

	arg_flag = 0;
	pipe = 0;
	token = mini->h_token;
	init_cmd(&cmd, &pipe, mini, &token);
	// if (!cmd)
	// 	return (error_manager);
	while (token)
	{
		// printf("token->str: %s\n", token->str);
		if (token && (token->type == INPUT || token->type == HEREDOC
			|| token->type == APPEND || token->type == TRUNC))
			check_file(mini, &cmd, &token);
		if (token && token->type == STR)
			check_cmd(mini, &cmd, &token, &arg_flag);
		if (token && token->type == PIPE)
		{
			new_cmd(&mini, &cmd, &arg_flag);
			init_cmd(&cmd, &pipe, mini, &token);
			arg_flag = 0;
			token = token->next;
		}
	}
	if (cmd && (cmd->args || cmd->builtin || cmd->in || cmd->out))
		new_cmd(&mini, &cmd, &arg_flag); // add last element, need if
}

static void	check_file(t_mini *mini, t_cmd **cmd, t_token **token)
{
	int	fd;
	
	if ((*token)->type == INPUT || (*token)->type == HEREDOC)
	{
		if (access((*token)->next->str, R_OK) == -1)
			return (cmd_skip(mini, cmd, token));
		else
			(*cmd)->in = (*token)->next->str;
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
			(*cmd)->out = (*token)->next->str;
	}
	(*token) = (*token)->next->next;
}
//manage skip builtin
static void	check_cmd(t_mini *mini, t_cmd **cmd, t_token **token, int *arg_flag)
{
	if (*arg_flag)
	{
		if ((*cmd)->builtin == EXPORT) //list cmmd !=0
		{
			return (cmd_skip(mini, cmd, token));
			return ;
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
	if ((*cmd)->builtin != NONE || access((*cmd)->args[0], X_OK) == 0)
		(*arg_flag)++;
	else
		return (cmd_skip(mini, cmd, token));
	(*token) = (*token)->next;
}

static void	init_cmd(t_cmd **cmd, int *pipe, t_mini *mini, t_token **token)
{
	if (*pipe == 0)
	{
		while ((*token))
		{
			if ((*token)->type == PIPE)
				(*pipe)++;
			(*token) = (*token)->next;
		}
		(*token) = mini->h_token;
		mini->cmd = NULL;
	}
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return ;
	(*cmd)->args = NULL;
	(*cmd)->in = NULL;
	(*cmd)->out = NULL;
	(*cmd)->fd[0] = -1;
	(*cmd)->fd[1] = -1;
	(*cmd)->pid = -1;
	(*cmd)->builtin = NONE;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}
