/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:54:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/01 15:50:44 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_mini *mini, t_cmd *cmd)
{
	t_sig	*sig;

	sig = get_sig();
	if (cmd->builtin == CD)
		sig->status = mini_cd(mini, cmd);
	if (cmd->builtin == ECHO)
		sig->status = mini_echo(mini, cmd);
	else if (cmd->builtin == ENV)
		sig->status = mini_env(mini, cmd);
	else if (cmd->builtin == EXPORT)
		sig->status = mini_export(mini, cmd);
	else if (cmd->builtin == PWD)
		sig->status = mini_pwd(mini, cmd);
	else if (cmd->builtin == UNSET)
		sig->status = mini_unset(mini, cmd);
	else if (cmd->builtin == EXIT)
		sig->status = mini_exit(mini, cmd);
	return (sig->status);
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
