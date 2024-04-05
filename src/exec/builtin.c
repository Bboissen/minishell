/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:04:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/03 16:18:08 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_mini *mini)
{
	if (mini->cmd->builtin == CD
		|| mini->cmd->builtin == ECHO
		|| mini->cmd->builtin == ENV
		|| mini->cmd->builtin == EXIT
		|| mini->cmd->builtin == EXPORT
		|| mini->cmd->builtin == PWD
		|| mini->cmd->builtin == UNSET)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * Execute a built-in command.
 * @param {char**} args - The arguments for the command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns the result of the command execution.
 */
int	exec_builtin(char **args, t_mini *mini)
{

	if (mini->cmd->builtin == CD)
		mini->sig.status = mini_cd(args, mini->env);
	if (mini->cmd->builtin == ECHO)
		mini->sig.status = mini_echo(mini);
	if (mini->cmd->builtin == ENV)
		mini->sig.status = mini_env(mini);
	if (mini->cmd->builtin == EXPORT)
		mini->sig.status = mini_export(args, mini->env, mini->env);
	if (mini->cmd->builtin == PWD)
		mini->sig.status = mini_pwd();
	if (mini->cmd->builtin == UNSET)
		mini->sig.status = mini_unset(mini);
	return (mini->sig.status);
}
