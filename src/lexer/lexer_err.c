/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:34:17 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/01 10:36:47 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_err(t_mini *mini, char *str, int err, char c)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = SYNTAX;
	mini->token = mini->h_token;
	if (err == QUOTE)
		ft_printfd(STDERR_FILENO, "%s: odd number of quotes\n", mini->name);
	else if(err == PARSE && c != 0)
		ft_printfd(STDERR_FILENO, "%s: syntax error near unexpected token `%c'\n", mini->name, c);
	else if(err == PARSE)
		ft_printfd(STDERR_FILENO, "%s: syntax error near unexpected token `newline'\n", mini->name);
	else if(err == END)
	{
		sig->status = SUCCESS;
		ft_printfd(STDERR_FILENO, "%s: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", mini->name, str);
	}
	else if (err == MALLOC)
		error_manager(mini, MALLOC, NULL, NULL);
	free_token(&(mini->h_token));
	mini->token = NULL;
}
