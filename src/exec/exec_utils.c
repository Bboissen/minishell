/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:54:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/24 17:38:39 by gdumas           ###   ########.fr       */
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
	(void)mini;
	if (cmd->in != NULL)
		cmd->fd[0] = open(cmd->in, O_RDONLY);
	if (cmd->out != NULL)
		cmd->fd[1] = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

