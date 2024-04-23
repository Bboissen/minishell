/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:03:28 by bbsn              #+#    #+#             */
/*   Updated: 2024/04/23 11:03:19 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_err(t_mini *mini, char *str, int err)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = err;
	if (err == EXE)
		dprintf(STDERR, "%s: %s: command not found\n", mini->name, str);
	else if(err == PERMISSION)
		dprintf(STDERR, "%s: permission denied %s\n", mini->name, str);
	else if(err == MISSING)
		dprintf(STDERR, "%s: no such file or directory: %s\n", mini->name, str);
	else
		error_manager(mini, MALLOC, NULL, NULL);
}