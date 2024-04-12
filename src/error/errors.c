/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:03 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/12 12:05:42 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infile(int argc, char **files)
{
	int	err;

	err = 0;
	if (access(files[1], R_OK) == -1)
	{
		err = errno;
		printf_fd(2, "%s: %s: %s\n", &files[0][2], strerror(errno), files[1]);
	}
	return (err);
}

int	check_outfile(int argc, char **files)
{
	int	fd;
	int	err;

	err = 0;
	fd = open(files[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd != -1)
		close(fd);
	if (fd == -1 || access(files[argc - 1], W_OK) == -1)
	{
		printf_fd(2, "%s: %s: %s\n",
			&files[0][2], strerror(errno), files[argc - 1]);
		return (1);
	}
	return (err);
}

static char	*error_handler(char const *s, t_list **cmd, char *exe, char **argv)
{
	((t_word *)((*cmd)->cont))->err = PERM_KO;
	printf_fd(2, "%s: permission denied: %s\n", &argv[0][2], s);
	exe = NULL;
	return (exe);
}

char	*check_perm(char const *s, t_list **cmd, char **argv, char **env)
{
	char	*temp;
	char	*exe;

	((t_word *)((*cmd)->cont))->err = 0;
	temp = ft_substr(s, ((t_word *)((*cmd)->cont))->start,
			((t_word *)((*cmd)->cont))->len);
	if (!temp)
		return (((t_word *)((*cmd)->cont))->err = MALLOC_KO, NULL);
	else if (access(temp, X_OK) == 0 && ((temp[0] == '.'
				&& temp[1] == '/') || temp[0] == '/'))
	{
		exe = ft_strdup(temp);
		if (!exe)
			((t_word *)((*cmd)->cont))->err = MALLOC_KO;
		return (free(temp), exe);
	}
	else if (((temp[0] == '.'
				&& temp[1] == '/') || temp[0] == '/') && errno == EACCES)
		exe = error_handler(s, cmd, exe, argv);
	else if (access(temp, X_OK) == -1)
		exe = cmd_finder(temp, cmd, argv, env);
	else if (errno == EACCES)
		exe = error_handler(s, cmd, exe, argv);
	return (free(temp), exe);
}

/**
 * Prints an error message based on the accessibility of the given path.
 * @param {char*} path - The path to check.
 * @return {int} - Returns CMD if the file does not exist or is not a command, 
 * DIRECTORY if the file is not executable.
 */
static int	error_message(char *path)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);

	if (access(path, F_OK) != 0)
		return (ft_putendl_fd(": No such file or directory", STDERR),
			CMD);
	else if (access(path, X_OK) != 0)
		return (ft_putendl_fd(": Permission denied", STDERR), DIRECTORY);
	else
		return (ft_putendl_fd(": command not found", STDERR), CMD);
}
