/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/30 11:39:25 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->name);
		mini->env->name = NULL;
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	mini_unset(t_mini *mini)
{
	char	**args;
	t_env	*env;
	t_env	*prev;
	int		i;

	args = mini->cmd->args;
	env = mini->h_env;
	i = 0;
	while (args[i])
	{
		prev = NULL;
		while (env)
		{
			if (!ft_strncmp(args[i], env->name, env_size(env->name)))
			{
				if (prev)
					prev->next = env->next;
				else
					mini->h_env = env->next;
				free_node(mini, env);
				break ;
			}
			prev = env;
			env = env->next;
		}
		env = mini->h_env;
		i++;
	}
	return (SUCCESS);
}
