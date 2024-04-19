/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:34:17 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/19 14:07:04 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//bash: export: `te@st=2': not a valid identifier

void	lexer_err(t_mini *mini, char **str, int err, char c)
{
	t_sig	*sig;

	sig = get_sig();
	if (err == QUOTE)
		dprintf(STDERR, "%s: odd number of quotes\n", mini->name);
	else if(err == PARSE && c != 0)
		dprintf(STDERR, "%s: syntax error near unexpected token '%c'\n", mini->name, c);
	else if(err == PARSE)
		dprintf(STDERR, "%s: syntax error near unexpected token 'newline'\n", mini->name);
	sig->status = err;
	mini->token = mini->h_token;
	free_token(&(mini->token));
	mini->h_token = NULL;
	*str = NULL;
	return ;
}
