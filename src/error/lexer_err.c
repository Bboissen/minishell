/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:34:17 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/06 16:54:07 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Error manager for the lexer.
 * 
 * @param mini Pointer to the main structure of the shell.
 * @param str The string that caused the error.
 * @param err The error code.
 * @param c The character that caused the error.
 */
void	lexer_err(t_mini *mini, char *str, int err, char c)
{
	get_sig()->status = SYNTAX;
	mini->token = mini->h_token;
	if (err == QUOTE)
		ft_printfd(STDERR_FILENO, "%s: odd number of quotes\n", mini->name);
	else if (err == PARSE && c != 0)
		ft_printfd(STDERR_FILENO, "%s: syntax error near unexpected \
token `%c'\n", mini->name, c);
	else if (err == PARSE)
		ft_printfd(STDERR_FILENO, "%s: syntax error near unexpected \
token `newline'\n", mini->name);
	else if (err == END)
	{
		get_sig()->status = SUCCESS;
		ft_printfd(STDERR_FILENO, "%s: warning: here-document at line 1 \
delimited by end-of-file (wanted `%s')\n", mini->name, str);
	}
	else if (err == MALLOC)
		error_manager(mini, MALLOC, NULL, NULL);
	free_token(&(mini->h_token));
	mini->token = NULL;
}
