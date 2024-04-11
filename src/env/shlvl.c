/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:07 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/11 17:22:11 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if a string represents a valid shell level.
 * @param {const char*} str - The string to check.
 * @return {int} - Returns SUCCESS if the string is a valid shell level, ERROR otherwise.
 */
static int	invalid_lvl(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (ERROR);
	return (SUCCESS);
}

/**
 * Get the shell level from a string.
 * @param {const char*} str - The string to get the level from.
 * @return {int} - Returns the shell level.
 */
static int	get_lvl(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_skip_spacenl(str, &i);
	if (invalid_lvl(str))
		return (FALSE);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
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

/**
 * Increment the shell level in the environment.
 * @param {t_env*} env - The environment to increment the shell level in.
 */
void	increment_shell_level(t_env *env)
{
	int		shell_level;
	char	*shlvl;
	char	*shell_level_value;

	shell_level_value = get_env_value("SHLVL", env);
	if (!ft_strcmp(shell_level_value, ""))
		free(shell_level_value);
	shell_level = get_lvl(shell_level_value) + 1;
	ft_memdel(shell_level_value);
	while (env && env->name)
	{
		if (!ft_strcmp(env->name, "SHLVL"))
		{
			ft_memdel(env->value);
			shlvl = ft_itoa(shell_level);
			env->value = ft_strdup(shlvl);
			ft_memdel(shlvl);
			return ;
		}
		env = env->next;
	}
}
