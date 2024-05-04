/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:35:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 10:44:35 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the environment variables.
 * 
 * @param mini The main structure of the shell.
 * @return {int} - Returns SUCCESS if the environment variables were 
 * printed successfully, the error number otherwise.
 */
int	mini_env(t_mini *mini, t_cmd *cmd)
{
	t_env	*env;
	int		fd;

	fd = set_fd(cmd);
	env = mini->h_env;
	while (env)
	{
		if (!env->value)
			ft_printfd(fd, "%s\n", env->name);
		else
			ft_printfd(fd, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (SUCCESS);
}

/**
 * @brief Sets the file descriptor for the command.
 * 
 * @param cmd A pointer to the command structure.
 * @return {int} - The file descriptor to be used for the command.
 */
static int	set_fd(t_cmd *cmd)
{
	if (cmd->fd[1] != -1)
		return (cmd->fd[1]);
	else
		return (STDOUT_FILENO);
}
