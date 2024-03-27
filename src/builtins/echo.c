/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:36:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/21 15:24:46 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	mini_echo(char **args)
{
	int	i;
	int	n_option;

	i = 0;
	n_option = 0;
	if (args[i])
	{
		while (ft_strcmp(args[i], "-n") == 0)
			n_option = 1;
		while (args[i])
		{
			ft_putstr_fd(args[i], STDOUT_FILENO);
			if (args[i + 1] && args[i][0] != '\0')
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}*/

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

int	mini_echo(t_mini *mini)
{
	size_t	i;
	int		n;
	char	**args;

	n = 1;
	args = mini->cmd->args;
	if (mini->sig.err != 1)
		mini->sig.status = 0;
	if (!args[1])
		return (ft_putchar_fd('\n', 1), TRUE);
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
