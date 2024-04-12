/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:04:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/12 11:53:45 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if a command is a built-in command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns TRUE if the command is a built-in command, 
 * otherwise returns FALSE.
 */
int	is_builtin(t_mini *mini)
{
	if (mini->cmd->builtin == NONE)
		return (FALSE);
	else
		return (TRUE);
}

/**
 * Execute a built-in command.
 * @param {char**} args - The arguments for the command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns the result of the command execution.
 */
void	exec_builtin(char **args, t_mini *mini)
{

	if (mini->cmd->builtin == CD)
		mini->sig.status = mini_cd(mini);
	else if (mini->cmd->builtin == ECHO)
		mini->sig.status = mini_echo(mini);
	else if (mini->cmd->builtin == ENV)
		mini->sig.status = mini_env(mini);
	else if (mini->cmd->builtin == EXPORT)
		mini->sig.status = mini_export(args, mini->env, mini->env);
	else if (mini->cmd->builtin == PWD)
		mini->sig.status = mini_pwd();
	else if (mini->cmd->builtin == UNSET)
		mini->sig.status = mini_unset(mini);
}
