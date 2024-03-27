/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:04:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 14:55:27 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if a command is a built-in command.
 * @param {char*} command - The command to check.
 * @return {int} - Returns ERROR if the command is a built-in command, otherwise returns SUCCESS.
 */
int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == SUCCESS
		|| ft_strcmp(command, "cd") == SUCCESS
		|| ft_strcmp(command, "pwd") == SUCCESS
		|| ft_strcmp(command, "env") == SUCCESS
		|| ft_strcmp(command, "export") == SUCCESS
		|| ft_strcmp(command, "unset") == SUCCESS)
		return (ERROR);
	else
		return (SUCCESS);
}

/**
 * Execute a built-in command.
 * @param {char**} args - The arguments for the command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns the result of the command execution.
 */
int	exec_builtin(char **args, t_mini *mini)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == SUCCESS)
		result = mini_echo(args);
	if (ft_strcmp(args[0], "cd") == SUCCESS)
		result = mini_cd(args, mini->env);
	if (ft_strcmp(args[0], "pwd") == SUCCESS)
		result = mini_pwd();
	if (ft_strcmp(args[0], "env") == SUCCESS)
		mini_env(mini->env);
	if (ft_strcmp(args[0], "export") == SUCCESS)
		mini_export(args, mini->env, mini->env);
	if (ft_strcmp(args[0], "unset") == SUCCESS)
		mini_unset(args, mini);
	return (result);
}
