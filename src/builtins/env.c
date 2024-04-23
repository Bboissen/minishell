/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:35:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/23 12:38:06 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print the environment variables.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns SUCCESS if the environment variables were 
 * printed successfully, the error number otherwise.
 */
int	mini_env(t_mini *mini)
{
	while (mini->env)
	{
		if (ft_printf("%s=%s\n", mini->env->name, mini->env->value) < 0)
		{
			perror("printf");
			return (errno);
		}
		mini->env = mini->env->next;
	}
	return (SUCCESS);
}
