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

static int	init_cmd(t_mini *mini, t_cmd **cmd, int skip);

void	cmd_setter(t_mini **mini, t_cmd **cmd, int skip, int *arg_flag)
{
	if (*cmd)
		new_cmd(mini, cmd, arg_flag);
	init_cmd((*mini), cmd, skip);
	get_sig()->status = 0;
	*arg_flag = 0;
}

int	parser(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		arg_flag;
	int		skip;

	arg_flag = 0;
	token = mini->h_token;
	init_cmd(mini, &cmd, 0);
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
			cmd_setter(&mini, &cmd, skip, &arg_flag);
			token = token->next;
		}
	}
	if (cmd)
		new_cmd(&mini, &cmd, &arg_flag);
	return (get_sig()->status);
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
