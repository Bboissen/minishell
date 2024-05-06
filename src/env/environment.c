/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:43:56 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/06 17:05:10 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		env_cpy(char **env_array, t_env **env, int *i);
static size_t	size_env_tab(t_env *env_lst);
static char		*append_name_value(t_env *env_lst, int i, int j, int k);

/**
 * @brief Initializes the environment linked list from an 
 * array of environment variables.
 * 
 * @param mini The mini structure.
 * @param env_array The array of environment variables.
 * @return {int} - Returns ERROR if memory allocation fails, 
 * otherwise returns SUCCESS.
 */
int	init_env(t_mini **mini, char **env_array)
{
	t_env	*env;
	t_env	*prev;
	int		i;

	env = NULL;
	prev = NULL;
	i = -1;
	while (env_array && env_array[++i])
	{
		if (env_cpy(env_array, &env, &i))
			return (error_manager(*mini, MALLOC, NULL, NULL));
		if (prev)
			prev->next = env;
		else
		{
			(*mini)->env = env;
			(*mini)->h_env = (*mini)->env;
		}
		prev = env;
	}
	return (SUCCESS);
}

/**
 * @brief Copies an environment variable from an array to a linked list.
 * 
 * @param mini The mini structure.
 * @param env_array The array of environment variables.
 * @param env The current node in the environment linked list.
 * @param i The index of the environment variable in the array.
 * @return {int} - Returns ERROR if memory allocation fails, 
 * otherwise returns SUCCESS.
 */
static int	env_cpy(char **env_array, t_env **env, int *i)
{
	char	*equals_pos;

	*env = malloc(sizeof(t_env));
	if (!(*env))
		return (ERROR);
	equals_pos = ft_strchr(env_array[*i], '=');
	if (equals_pos != NULL)
	{
		(*env)->name = ft_strndup(env_array[*i], equals_pos - env_array[*i]);
		if (!(*env)->name)
			return (free(*env), ERROR);
		(*env)->value = ft_strdup(ft_strchr(env_array[*i], '=') + 1);
	}
	else
	{
		(*env)->name = ft_strdup(env_array[*i]);
		if (!(*env)->name)
			return (free(*env), ERROR);
		(*env)->value = ft_strdup("");
	}
	if (!(*env)->value)
		return (free((*env)->name), free(*env), ERROR);
	(*env)->next = NULL;
	return (SUCCESS);
}

/**
 * @brief Converts the environment list into an array of strings.
 * 
 * @param env The environment list.
 * @return {char **} - Returns an array of strings, each string 
 * being a name-value pair from the environment list.
 */
char	**env_to_tab(t_mini *mini)
{
	t_env	*tmp;
	char	**tab;
	int		size;
	int		i;

	if (!mini->h_env)
		return (NULL);
	size = size_env_tab(mini->h_env);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tmp = mini->h_env;
	i = 0;
	while (tmp)
	{
		tab[i++] = append_name_value(tmp, -1, -1, -1);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	mini->env = mini->h_env;
	return (tab);
}

/**
 * @brief Calculates the size of the environment list.
 * 
 * @param env_lst The environment list.
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
 * @brief Appends the name and value of an environment variable into a string.
 * 
 * @param env_lst The node of the environment list.
 * @return {char *} - Returns a string with the format "name=value".
 */
static char	*append_name_value(t_env *env_lst, int i, int j, int k)
{
	char	*env_str;
	size_t	size;

	size = ft_strlen(env_lst->name) + 1;
	if (env_lst->value)
		size += ft_strlen(env_lst->value) + 1;
	env_str = malloc(sizeof(char) * size);
	if (!env_str)
		return (NULL);
	if (env_lst->name)
	{
		while (env_lst->name[++j])
			env_str[++i] = env_lst->name[j];
	}
	if (env_lst->value)
	{
		env_str[++i] = '=';
		while (env_lst->value[++k])
			env_str[++i] = env_lst->value[k];
	}
	env_str[++i] = '\0';
	return (env_str);
}
