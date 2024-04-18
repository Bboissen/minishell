/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:35:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 13:15:59 by gdumas           ###   ########.fr       */
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
	mini->sig.status = 0;
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
