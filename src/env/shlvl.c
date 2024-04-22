/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:07 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/22 11:47:20 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if a string represents a valid shell level.
 * 
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
 * 
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
 * Increment the shell level in the environment.
 * 
 * @param {t_env*} env - The environment to increment the shell level in.
 */
void	increment_shell_level(t_mini **mini)
{
	char	*shell_level_value;
	int		shell_level;
	char	*shlvl;

	shell_level_value = expand_token(mini, "SHLVL"); //protected
	shell_level = get_lvl(shell_level_value) + 1;
	if (shell_level_value)
		ft_memdel(shell_level_value);
	while ((*mini)->env && (*mini)->env->name)
	{
		if (!ft_strcmp((*mini)->env->name, "SHLVL"))
		{
			ft_memdel((*mini)->env->value);
			shlvl = ft_itoa(shell_level); //protected
			if (!shlvl)
			{
				(*mini)->env->value = NULL;
				error_manager(*mini, MALLOC);
			}
			(*mini)->env->value = ft_strdup(shlvl); //protected
			if (!(*mini)->env->value)
			{
				ft_memdel(shlvl);
				error_manager(*mini, MALLOC);
			}
			ft_memdel(shlvl);
			return ;
		}
		(*mini)->env = (*mini)->env->next;
	}
}
