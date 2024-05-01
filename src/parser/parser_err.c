/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:03:28 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/01 17:30:23 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_err(t_mini *mini, char *str, int err)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = 1; //for file but not for command
	if (err != MALLOC && err != EXE)
		ft_printfd(STDERR_FILENO, "%s: %s: %s\n", mini->name, str, strerror(err));
	if (err == EXE)
		ft_printfd(STDERR_FILENO, "%s: %s: command not found\n", mini->name, str);
	else if (err == MALLOC)
		error_manager(mini, MALLOC, NULL, NULL);
}