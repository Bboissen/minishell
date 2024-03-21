/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:35:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/20 17:45:46 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_mini *mini)
{
	size_t	i;

	i = 0;
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
	return (TRUE);
}
