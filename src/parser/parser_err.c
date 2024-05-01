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
	// printf("parser_err %d\n", err);
	sig->status = 1; //directory to manage
	if (err != MALLOC && err != EXE)
	{
		ft_printfd(STDERR_FILENO, "%s: %s: %s\n", mini->name, str, strerror(err));
	}
	else if (err == EXE)
	{
		sig->status = 127;
		ft_printfd(STDERR_FILENO, "%s: %s: command not found\n", mini->name, str);
	}
	else if (err == MALLOC)
		error_manager(mini, MALLOC, NULL, NULL);
}