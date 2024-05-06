/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:35:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/06 17:07:58 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the environment variables.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
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
