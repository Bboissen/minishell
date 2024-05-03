/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:36:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 16:20:30 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static size_t	check_n(char **args)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (args[j])
	{
		if (args[j][0] == '-')
		{
			k = 1;
			while (args[j][k] == 'n')
				k++;
			if (args[j][k] == '\0')
				j++;
			else
				break ;
		}
		else
			break ;
	}
	return (j);
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
	i = check_n(args);
	if (i > 0)
		n_opt = TRUE;
	while (args && args[i] != (void *)0)
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
