/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:07 by bbsn              #+#    #+#             */
/*   Updated: 2024/04/15 14:47:07 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_read(t_mini *mini, t_cmd **cmd, t_token *token);
static void	check_write(t_mini *mini, t_cmd **cmd, t_token *token);
static void	check_cmd(t_mini *mini, t_cmd **cmd, t_token *token, int *arg_flag);
static void	init_cmd(t_cmd **cmd, int *pipe, t_mini *mini, t_token *token);

void	parser(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		arg_flag;
	int		pipe;

	arg_flag = 0;
	pipe = 0;
	token = mini->h_token;
	init_cmd(&cmd, &pipe, mini, token);
	// if (!cmd)
	// 	return (error_manager);
	while (token)
	{
		if (token->type == INPUT || token->type == HEREDOC)
			check_read(mini, &cmd, token);
		else if (token->type == APPEND || token->type == TRUNC)
			check_write(mini, &cmd, token);
		else if (token->type == STR)
			check_cmd(mini, &cmd, token, &arg_flag);
		else if (token->type == PIPE)
		{
			new_cmd(mini, &cmd, &arg_flag);
			init_cmd(&cmd, &pipe, mini, token);
		}
	}
}

static void	check_read(t_mini *mini, t_cmd **cmd, t_token *token)
{
	if (access(token->next->str, R_OK) == -1)
		cmd_skip(mini, token);
	else
		(*cmd)->in = token->next->str;
	token = token->next;
}

static void	check_write(t_mini *mini, t_cmd **cmd, t_token *token)
{
	int	fd;

	if (token->type == APPEND)
		fd = open(token->next->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (token->type == TRUNC)
		fd = open(token->next->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd >= 0)
		close(fd);
	if (fd < 0 || access(token->next->str, W_OK) == -1)
		cmd_skip(mini, token);
	else
		(*cmd)->out = token->next->str;
	token = token->next;
}

static void	check_cmd(t_mini *mini, t_cmd **cmd, t_token *token, int *arg_flag)
{
	if (arg_flag)
	{
		if (PIPE && (*cmd)->builtin == EXPORT)
		{
			cmd_skip(mini, token);
			return ;
		}
		(*cmd)->args = add_args(cmd, token->str);
		token = token->next;
		return ;
	}
	if (!check_blt(cmd, token->next->str) && !ft_strchr(token->next->str, '/'))
		path_finder(mini, *cmd, token->next->str);
	if (((*cmd)->builtin && (*cmd)->builtin != CD)
		|| access((*cmd)->args[0], X_OK))
		token = token->next;
	else
		cmd_skip(mini, token);
}

static void	init_cmd(t_cmd **cmd, int *pipe, t_mini *mini, t_token *token)
{
	if (*pipe == 0)
	{
		while (token)
		{
			if (token->type == PIPE)
				(*pipe)++;
			token = token->next;
		}
		token = mini->h_token;
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
