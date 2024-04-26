/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:54:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/26 16:19:40 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_mini *mini)
{
	t_sig	*sig;

	sig = get_sig();
	if (mini->cmd->builtin == CD)
		sig->status = mini_cd(mini);
	if (mini->cmd->builtin == ECHO)
		sig->status = mini_echo(mini);
	else if (mini->cmd->builtin == ENV)
		sig->status = mini_env(mini);
	else if (mini->cmd->builtin == EXPORT)
		sig->status = mini_export(mini);
	else if (mini->cmd->builtin == PWD)
		sig->status = mini_pwd(mini);
	else if (mini->cmd->builtin == UNSET)
		sig->status = mini_unset(mini);
	else if (mini->cmd->builtin == EXIT)
		sig->status = mini_exit(mini);
}

void	fd_handler(t_mini *mini, t_cmd *cmd)
{
	int	in;
	int	out;
	
	(void)mini;
	if (cmd->in != NULL)
	{
		in = open(cmd->in, O_RDONLY);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->out != NULL)
	{
		out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
