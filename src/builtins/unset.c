/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 14:45:15 by bboissen         ###   ########.fr       */
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

static void	link_env(t_mini *mini, char *args)
{
	t_env	*tmp;

	while (mini->env && mini->env->next)
	{
		if (ft_strncmp(args, mini->env->next->name,
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

int	mini_unset(t_mini *mini, t_cmd *cmd)
{
	char	**args;
	t_env	*env;
	int		i;

	args = cmd->args;
	env = mini->h_env;
	i = 0;
	while (arg_exists(args, i))
	{
		if (!ft_strncmp(args[i], env->name,
				env_size(env->name)))
		{
			if (env->next)
				env = env->next;
			free_node(mini, env);
		}
		link_env(mini, args[i]);
		i++;
	}
	return (SUCCESS);
}
