/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:42:56 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 09:40:59 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Error manager for the export command.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param error The error code.
 * @param arg The argument that caused the error.
 */
void	export_err(t_mini *mini, int error, char *arg)
{
	t_sig	*sig;

	sig = get_sig();
	(void) error;
	sig->status = 1;
	ft_printfd(STDERR_FILENO, "%s: export: `%s': \
not a valid identifier\n", mini->name, arg);
}

/**
 * @brief Error manager for the cd command.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param err The error code.
 * @param arg The argument that caused the error.
 */
void	cd_err(t_mini *mini, int err, char *arg)
{
	get_sig()->status = err;
	if (err == errno)
		ft_printfd(STDERR_FILENO, "%s: %s: %s\n",
			mini->name, arg, strerror(err));
	else if (err == ERROR)
		ft_printfd(STDERR_FILENO, "%s: cd: \
too many arguments\n", mini->name);
	else if (err == MISSING)
		ft_printfd(STDERR_FILENO, "%s: cd: \
%s not set\n", mini->name, arg);
	else if (err == DIRECTORY)
		ft_printfd(STDERR_FILENO, "cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n");
	else
		error_manager(mini, MALLOC, NULL, NULL);
}

/**
 * @brief Error manager for the exit command.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param error The error code.
 * @param arg The argument that caused the error.
 */
void	exit_err(t_mini *mini, int error, char *arg)
{
	if (error == SYNTAX)
	{
		ft_printfd(STDERR_FILENO,
			"%s: exit: %s: numeric argument required\n",
			mini->name, arg);
		get_sig()->status = SYNTAX;
	}
	if (error == ERROR)
	{
		ft_printfd(STDERR_FILENO,
			"%s: exit: too many arguments\n", mini->name);
		get_sig()->status = ERROR;
	}
}
