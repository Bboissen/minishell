/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:43:56 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/11 17:18:15 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Calculate the size of the environment list.
 * @param {t_env*} lst - The environment list.
 * @return {size_t} - Returns the size of the environment list.
 */
static size_t	size_env(t_env *env_lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (env_lst)
	{
		if (env_lst->name)
		{
			lst_len += ft_strlen(env_lst->name);
			lst_len += 1;
			if (env_lst->value != NULL)
				lst_len += ft_strlen(env_lst->value);
		}
		if (env_lst->next)
			lst_len += 1;
		env_lst = env_lst->next;
	}
	return (lst_len);
}

/**
 * Appends the name and value of an environment variable to a string.
 * @param {char*} env_str - The string to append to.
 * @param {t_env*} lst - The current node in the environment linked list.
 * @param {int*} i - The current position in the string.
 * @return {char*} - Returns the updated string.
 */
char	*append_name_value(char *env_str, t_env *env_lst, int *i)
{
	int	j;
	int	k;

	j = -1;
	k = -1;
	if (env_lst->name)
	{
		while (env_lst->name[++j])
			env_str[++(*i)] = env_lst->name[j];
		env_str[++(*i)] = '=';
	}
	if (env_lst->value)
	{
		while (env_lst->value[++k])
			env_str[++(*i)] = env_lst->value[k];
	}
	return (env_str);
}

/**
 * Converts the environment list to a string.
 * @param {t_env*} lst - The environment list.
 * @return {char*} - Returns a string representation of the environment list.
 */
char	*env_to_str(t_env *env_lst)
{
	char	*env_str;
	int		i;

	i = -1;
	env_str = malloc(sizeof(char) * size_env(env_lst) + 1);
	if (!env_str)
		return (NULL);
	while (env_lst)
	{
		env_str = append_name_value(env_str, env_lst, &i);
		if (!env_str)
			return (NULL);
		if (env_lst->next != NULL)
			env_str[++i] = '\n';
		env_lst = env_lst->next;
	}
	env_str[++i] = '\0';
	return (env_str);
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
int	env_cpy(t_mini *mini, char **env_array, t_env *env, int *i)
{
	char	*equals_pos;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	strchr(env_array[*i], '=');
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
	env->next = new;
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
	i = 0;
	while (env_array && env_array[0] && env_array[++i])
		if (env_cpy(mini, env_array, env, &i))
			return (ERROR);
	return (SUCCESS);
}
