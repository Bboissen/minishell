/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/24 15:59:40 by gdumas           ###   ########.fr       */
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

static void	link_env(t_mini *mini, char **args)
{
	t_env	*tmp;

	while (mini->env && mini->env->next)
	{
		if (ft_strncmp(args[1], mini->env->next->name,
				env_size(mini->env->next->name)) == 0)
		{
			tmp = mini->env->next->next;
			free_node(mini, mini->env->next);
			mini->env->next = tmp;
			return ;
		}
		mini->env = mini->env->next;
	}
}

int	mini_unset(t_mini *mini)
{
	char	**args;
	t_env	*env;

	args = mini->cmd->args;
	env = mini->h_env;
	if ((args[1]))
	{
		if (!ft_strncmp(args[1], env->name,
				env_size(env->name)))
		{
			if (env->next)
				env = env->next;
			return (free_node(mini, env), SUCCESS);
		}
		link_env(mini, args);
		return (SUCCESS);
	}
	return (ft_printfd(2,
			"minishell: unset: '%s': not a valid identifier\n",
			mini->cmd->args[1]), SUCCESS);
}
