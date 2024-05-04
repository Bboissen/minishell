/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:03:28 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/03 15:41:02 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_err(t_mini *mini, char *str, int err)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = 1;
	if (err == DIRECTORY)
	{
		sig->status = DIRECTORY;
		ft_printfd(STDERR_FILENO, "%s: %s: Is a directory\n", mini->name, str);
	}
	else if (err != MALLOC && err != EXE && err != MISSING)
	{
		ft_printfd(STDERR_FILENO, "%s: %s: %s\n", mini->name, str, strerror(err));
	}
	else if (err == EXE)
	{
		sig->status = EXE;
		ft_printfd(STDERR_FILENO, "%s: %s: command not found\n", mini->name, str);
	}
	else if (err == MISSING)
	{
		sig->status = EXE;
		ft_printfd(STDERR_FILENO, "%s: %s: No such file or directory\n", mini->name, str);
	}
	else if (err == MALLOC)
		error_manager(mini, MALLOC, NULL, NULL);
}
