/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:36:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 18:37:17 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if the '-n' option is present in the arguments.
 * @param {char**} args - The arguments for the echo command.
 * @return {size_t} - Returns the index of the first argument after 
 * the '-n' options if they are present, ERROR otherwise.
 */
static size_t	check_n(char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][j++] == '-' && args[i][j] && args[i][j] == 'n')
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (ERROR);
		}
		else
			return (i);
	}
	return (i);
}

/**
 * Execute the echo command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns SUCCESS if the command was executed successfully & 
 * SUCCESS if there are no arguments
 */
int	mini_echo(t_mini *mini)
{
	size_t	i;
	int		n;
	char	**args;

	n = 1;
	args = mini->cmd->args;
	if (!args[1])
		return (ft_putchar_fd('\n', 1), SUCCESS);
	if ((ft_strequ(args[1], " ") && !args[2]))
		return (SUCCESS);
	i = check_n(args);
	if (i > 1)
		n = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i++])
			ft_putchar_fd(' ', 1);
	}
	if (n)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
