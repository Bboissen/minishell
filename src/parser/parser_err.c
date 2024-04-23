/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbsn <bbsn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:03:28 by bbsn              #+#    #+#             */
/*   Updated: 2024/04/23 10:25:02 by bbsn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_err(t_mini *mini, char *str, int err, char c)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = err;
	if (err == EXE)
		dprintf(STDERR, "%s: %s: command not found\n", mini->name, str);
	else if(err == PARSE && c != 0)
		dprintf(STDERR, "%s: syntax error near unexpected token '%c'\n", mini->name, c);
	else if(err == PARSE)
		dprintf(STDERR, "%s: syntax error near unexpected token 'newline'\n", mini->name);
	else
		error_manager(mini, MALLOC, NULL, NULL);
	cmd_skip(mini, &mini->cmd, &mini->token);
}