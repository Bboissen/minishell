/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 15:19:08 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_env_len(char **env_tab)
{
	int	i;

	i = 0;
	while (env_tab[i])
		i++;
	return (i);
}

/**
 * Sets or updates an environment variable in the environment list.
 * @param {t_env**} env - The pointer to the environment list.
 * @param {char*} name - The name of the environment variable to set.
 * @param {char*} value - The value to set the environment variable to.
 * If the environment variable already exists, its value is updated.
 * If it does not exist, a new environment variable is created.
 */
void	set_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_env));
	tmp->name = strdup(name);
	tmp->value = strdup(value);
	tmp->next = *env;
	*env = tmp;
}

/**
 * Retrieves the value of an environment variable by its name.
 * @param {t_env*} env - The environment list.
 * @param {char*} name - The name of the environment variable.
 * @return {char*} - Returns the value of the environment variable if
 * found, NULL otherwise.
 */
char	*get_env(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * Sort an array of strings in ascending order.
 * @param {char**} tab - The array to sort.
 * @param {int} env_len - The length of the array.
 */
void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = FALSE;
	while (tab && ordered == FALSE)
	{
		i = -1;
		while (++i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = TRUE;
			}
		}
		env_len--;
	}
}

/**
 * Print the environment variables in sorted order.
 * @param {t_env*} env - The environment to print.
 */
void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;

	tab = env_to_tab(env);
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(tab[i]);
		i++;
	}
	free_tab(tab);
}
