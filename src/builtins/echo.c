/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:36:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 10:21:26 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the '-n' option is present in the arguments.
 * 
 * @param args The array of arguments.
 * @return size_t Returns FALSE if '-n' option is present, TRUE otherwise.
 */
static size_t	check_n(char **args)
{
	size_t	j;

	j = 0;
	while (args[0][j])
	{
		if (args[0][j] == '-' && args[0][j++] && args[0][j] == 'n')
		{
			while (args[0][j] == 'n')
				j++;
			if (args[0][j])
				return (FALSE);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (FALSE);
}

/**
 * @brief Executes the echo command.
 * 
 * @param mini The mini structure containing the command and its arguments.
 * @return int Returns SUCCESS after executing the command.
 */
int	mini_echo(t_mini *mini, t_cmd *cmd)
{
	size_t	i;
	int		n_opt;
	char	**args;
	int		fd;

	(void)mini;
	if (cmd->fd[1] != -1)
		fd = cmd->fd[1];
	else
		fd = STDOUT_FILENO;
	n_opt = FALSE;
	args = cmd->args;
	if (!args)
		return (ft_putchar_fd('\n', fd), SUCCESS);
	i = 0;
	if (check_n(args))
	{
		n_opt = TRUE;
		i++;
	}
	while (args && args[i] != (void *)0 && get_sig()->status != INTERUPT)
	{
		ft_printfd(fd, args[i]);
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!n_opt)
		ft_putchar_fd('\n', fd);
	return (SUCCESS);
}
