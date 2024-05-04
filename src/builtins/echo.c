/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:36:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 10:44:13 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_fd(t_cmd *cmd);
static void		print_args(int fd, char **args, size_t start, int n_opt);
static size_t	check_n(char **args);

/**
 * @brief Executes the echo command.
 * 
 * @param mini The mini structure containing the command and its arguments.
 * @return {int} - Returns SUCCESS after executing the command.
 */
int	mini_echo(t_mini *mini, t_cmd *cmd)
{
	size_t	i;
	int		n_opt;
	char	**args;
	int		fd;

	(void)mini;
	fd = set_fd(cmd);
	n_opt = FALSE;
	args = cmd->args;
	if (!args)
		return (ft_putchar_fd('\n', fd), SUCCESS);
	i = check_n(args);
	if (i > 0)
		n_opt = TRUE;
	print_args(fd, args, i, n_opt);
	return (SUCCESS);
}

/**
 * @brief Sets the file descriptor for the command.
 * 
 * @param cmd A pointer to the command structure.
 * @return {int} - The file descriptor to be used for the command.
 */
static int	set_fd(t_cmd *cmd)
{
	if (cmd->fd[1] != -1)
		return (cmd->fd[1]);
	else
		return (STDOUT_FILENO);
}

/**
 * @brief Prints the arguments to the specified file descriptor.
 *
 * @param fd The file descriptor to print to.
 * @param args The arguments to print. 
 * This should be a null-terminated array of strings.
 * @param start The index of the first argument to print.
 * @param n_opt A flag indicating whether to print 
 * a newline character at the end.
 */
static void	print_args(int fd, char **args, size_t start, int n_opt)
{
	size_t	i;

	i = start;
	while (args && args[i] != (void *)0)
	{
		ft_printfd(fd, args[i]);
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!n_opt)
		ft_putchar_fd('\n', fd);
}

/**
 * @brief Checks for the presence of '-n' in the arguments.
 *
 * @param args The arguments to check. 
 * This should be a null-terminated array of strings.
 * @return {size_t} - The number of arguments that start with '-n'.
 */
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
