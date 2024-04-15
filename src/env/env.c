/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:43:56 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 12:52:46 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Calculates the size of the environment list.
 * @param {t_env*} env_lst - The environment list.
 * @return {size_t} - Returns the number of nodes in the list.
 */
static size_t	size_env_tab(t_env *env_lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (env_lst)
	{
		lst_len++;
		env_lst = env_lst->next;
	}
	return (lst_len);
}

/**
 * Appends the name and value of an environment variable into a string.
 * @param {t_env*} env_lst - The node of the environment list.
 * @return {char*} - Returns a string with the format "name=value".
 */
static char	*append_name_value(t_env *env_lst)
{
	char	*env_str;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	env_str = malloc(sizeof(char) * (ft_strlen(env_lst->name)
				+ ft_strlen(env_lst->value) + 2));
	if (!env_str)
		return (NULL);
	if (env_lst->name)
	{
		while (env_lst->name[++j])
			env_str[++i] = env_lst->name[j];
		env_str[++i] = '=';
	}
	if (env_lst->value)
	{
		while (env_lst->value[++k])
			env_str[++i] = env_lst->value[k];
	}
	env_str[++i] = '\0';
	return (env_str);
}

/**
 * Converts the environment list into an array of strings.
 * @param {t_env*} env - The environment list.
 * @return {char**} - Returns an array of strings, each string being a name-value pair from the environment list.
 */
static char	**env_to_tab(t_env *env)
{
	t_env	*tmp;
	char	**tab;
	int		size;
	int		i;

	if (!env)
		return (NULL);
	size = size_env_tab(env);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		tab[i++] = append_name_value(tmp);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

/**
 * Copies an environment variable from an array to a linked list.
 * @param {t_mini*} mini - The mini structure.
 * @param {char**} env_array - The array of environment variables.
 * @param {t_env*} env - The current node in the environment linked list.
 * @param {int} i - The index of the environment variable in the array.
 * @return {int} - Returns ERROR if memory allocation fails, 
 * otherwise returns SUCCESS.
 */
static int	env_cpy(t_mini *mini, char **env_array, t_env *env, int *i)
{
	char	*equals_pos;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	equals_pos = strchr(env_array[*i], '=');
	if (equals_pos != NULL)
	{
		new->name = strndup(env_array[*i], equals_pos - env_array[*i]);
		new->value = ft_strdup(ft_strchr(env_array[*i], '=') + 1);
	}
	else
	{
		new->name = ft_strdup(env_array[*i]);
		new->value = ft_strdup("");
	}
	new->next = NULL;
	env = new;
	if (*i == 0)
		mini->h_env = env;
	env = env->next;
	return (SUCCESS);
}

/**
 * Initializes the environment linked list from an 
 * array of environment variables.
 * @param {t_mini*} mini - The mini structure.
 * @param {char**} env_array - The array of environment variables.
 * @return {int} - Returns ERROR if memory allocation fails, 
 * otherwise returns SUCCESS.
 */
int	init_env(t_mini *mini, char **env_array)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (ERROR);
	i = -1;
	while (env_array && env_array[++i])
		if (env_cpy(mini, env_array, env, &i))
			return (ERROR);
	return (SUCCESS);
}
