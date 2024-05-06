/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:03:28 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/06 16:53:46 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Error manager for the parser.
 * 
 * @param mini The main structure of the shell.
 * @param str The string to be printed.
 * @param err The error code.
 */
void	parser_err(t_mini *mini, char *str, int err)
{
	if (get_sig()->status != 126)
		get_sig()->status = 1;
	if (err == DIRECTORY)
	{
		get_sig()->status = DIRECTORY;
		ft_printfd(STDERR_FILENO, "%s: %s: Is a directory\n", mini->name, str);
	}
	else if (err != MALLOC && err != EXE && err != MISSING)
		ft_printfd(STDERR_FILENO, "%s: %s: %s\n",
			mini->name, str, strerror(err));
	else if (err == EXE)
	{
		get_sig()->status = EXE;
		ft_printfd(STDERR_FILENO, "%s: %s: command not found\n",
			mini->name, str);
	}
	else if (err == MISSING)
	{
		get_sig()->status = EXE;
		ft_printfd(STDERR_FILENO, "%s: %s: No such file or directory\n",
			mini->name, str);
	}
	else if (err == MALLOC)
		error_manager(mini, MALLOC, NULL, NULL);
}
