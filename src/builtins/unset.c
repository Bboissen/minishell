/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/16 09:49:10 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Calculate the size of an environment variable up to the '=' character.
 * @param {char*} env - The environment variable.
 * @return {size_t} - Returns the size of the environment variable.
 */
static size_t	env_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

/**
 * Free the memory allocated for an environment variable node.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {t_env*} env - The environment variable node to free.
 */
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

/**
 * Link the environment variables in the shell, skipping the one to be unset.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char**} args - The arguments for the unset command.
 * @return {int} - Returns SUCCESS if the linking was successful.
 */
static int	link_env(t_mini *mini, char **args)
{
	t_env	*tmp;

	while (mini->env && mini->env->next)
	{
		if (ft_strncmp(args[1], mini->env->next->value,
				env_size(mini->env->next->)) == 0)
		{
			tmp = mini->env->next->next;
			free_node(mini, mini->env->next);
			mini->env->next = tmp;
			return (SUCCESS);
		}
		mini->env = mini->env->next;
	}
}

/**
 * Unset an environment variable in the shell.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns SUCCESS if the variable was unset successfully.
 */
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
