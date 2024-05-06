/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:07 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/06 16:57:32 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shell_level(t_mini **mini, int shell_level);
static int	get_lvl(const char *str);
static int	invalid_lvl(const char *str);

/**
 * @brief Increment the shell level in the environment at minishell booting.
 * 
 * @param env The environment to increment the shell level in.
 */
void	increment_shell_level(t_mini **mini)
{
	char	*shell_level_value;
	int		shell_level;

	shell_level_value = expand_token(mini, "SHLVL");
	if (!shell_level_value)
		error_manager(*mini, MALLOC, NULL, NULL);
	shell_level = get_lvl(shell_level_value) + 1;
	if (shell_level_value)
		ft_memdel(shell_level_value);
	while ((*mini)->env && (*mini)->env->name)
	{
		update_shell_level(mini, shell_level);
		(*mini)->env = (*mini)->env->next;
	}
}

/**
 * @brief If found, updates the shell level in the environment.
 *
 * @param mini A double pointer to the t_mini structure,
 * which contains the environment.
 * @param shell_level The new shell level to be set.
 */
static void	update_shell_level(t_mini **mini, int shell_level)
{
	char	*shlvl;

	if (!ft_strcmp((*mini)->env->name, "SHLVL"))
	{
		ft_memdel((*mini)->env->value);
		shlvl = ft_itoa(shell_level);
		if (!shlvl)
		{
			(*mini)->env->value = NULL;
			error_manager(*mini, MALLOC, NULL, NULL);
		}
		(*mini)->env->value = ft_strdup(shlvl);
		if (!(*mini)->env->value)
		{
			ft_memdel(shlvl);
			error_manager(*mini, MALLOC, NULL, NULL);
		}
		ft_memdel(shlvl);
		return ;
	}
}

/**
 * @brief Get the shell level from the SHLVL env value.
 * 
 * @param str The string to get the level from.
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
 * @brief Check if a string represents a valid shell level.
 * 
 * @param str The string to check.
 * @return {int} - Returns SUCCESS if the string is
 * a valid shell level, ERROR otherwise.
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
