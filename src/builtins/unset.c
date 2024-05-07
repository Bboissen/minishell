/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:52 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 09:40:59 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*unset_env_var(t_mini *mini, char *args,
					t_env *curr, t_env *prev);
static void		free_node(t_mini *mini, t_env *env);
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
	t_env	*prev;
	t_env	*curr;
	t_env	*next;
	int		i;

	args = cmd->args;
	i = 0;
	while (arg_exists(args, i))
	{
		prev = NULL;
		curr = mini->h_env;
		while (curr)
		{
			next = unset_env_var(mini, args[i], curr, prev);
			if (next != curr)
				prev = curr;
			curr = next;
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Unsets an environment variable.
 *
 * @param mini Pointer to the t_mini structure, 
 * which contains the head of the environment variables list.
 * @param args The name of the environment variable to be unset.
 * @param curr Pointer to the current node in the environment variables list.
 * @param prev Pointer to the previous node in the environment variables list.
 */
static t_env	*unset_env_var(t_mini *mini, char *args,
			t_env *curr, t_env *prev)
{
	t_env	*next;

	next = curr->next;
	if (!ft_strncmp(args, curr->name, env_size(curr->name)))
	{
		if (prev == NULL)
			mini->h_env = next;
		else
			prev->next = next;
		free_node(mini, curr);
	}
	return (next);
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
