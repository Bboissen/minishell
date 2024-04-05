/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:24:38 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/05 11:25:02 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if a character is valid in an environment variable name.
 * @param {int} c - The character to check.
 * @return {int} - Returns 1 if the character is valid, 0 otherwise.
 */
int	is_env_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

/*not used*/
/**
 * Check if an environment variable is valid.
 * @param {const char*} env - The environment variable to check.
 * @return {int} - Returns 1 if the variable is valid, 0 if the name starts with a digit, -1 if the name contains invalid characters, 2 if there is no '=' character.
 */
int	is_valid_env(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]))
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (!ft_isalnum(env[i]))
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

/**
 * Calculate the length of the value of an environment variable.
 * @param {const char*} env - The environment variable.
 * @return {int} - Returns the length of the value.
 */
static int	env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	while (env[++i])
		size_name++;
	return (size_name);
}

/**
 * Get the value of an environment variable.
 * @param {char*} env - The environment variable.
 * @return {char*} - Returns a string containing the value of the variable.
 */
static char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	env_value = malloc(sizeof(char) * size_alloc);
	if (!env_value)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	j = 0;
	while (env[++i])
		env_value[j++] = env[i];
	env_value[j] = '\0';
	return (env_value);
}

/**
 * Get the value of an environment variable from a list of variables.
 * @param {char*} arg - The name of the variable.
 * @param {t_env*} env - The list of environment variables.
 * @return {char*} - Returns a string containing the value of the 
 * variable, or an empty string if the variable is not found.
 */
char	*get_env_value(char *arg, t_env *env)
{
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->name)
	{
		if (!ft_strcmp(arg, env->name))
		{
			env_val = ft_strdup(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}
