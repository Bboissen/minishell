/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 11:48:51 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_node(t_mini *mini, t_env *env);
static void		link_env(t_mini *mini, char *args);
static size_t	env_size(char *env);

/**
 * @brief Executes the unset command in a mini shell.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @return {int} - Returns the status of the command execution.
 */
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

/**
 * @brief Frees a node from the environment variables list.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param env Pointer to the environment variable node to be freed.
 */
static void	free_node(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->name);
		ft_memdel(mini->env->value);
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->name);
	ft_memdel(env->value);
	ft_memdel(env);
}

/**
 * @brief Links the environment variables in the list.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param args Pointer to the argument string.
 */
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

/**
 * @brief Calculates the size of an environment variable string.
 * 
 * @param env Pointer to the environment variable string.
 * @return {size_t} - Returns the size of the environment variable string.
 */
static size_t	env_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}
