/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:35:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/25 15:21:55 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the environment variables.
 * 
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns SUCCESS if the environment variables were 
 * printed successfully, the error number otherwise.
 */
int	mini_env(t_mini *mini)
{
	t_env	*env;

	env = mini->h_env;
	while (env)
	{
		if (ft_printfd(1, "%s=%s\n", env->name, env->value) < 0)
		{
			perror("printf");
			return (errno);
		}
		env = env->next;
	}
	return (SUCCESS);
}
