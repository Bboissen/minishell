/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:34:17 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/09 15:39:37 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_err(int err, char c)
{
	if (err == QUOTE)
	{
		dprintf(STDERR, "minishell: odd number of quotes\n");
		return (QUOTE);
	}
	else if(err == PARSE)
	{
		dprintf(STDERR, "minishell: syntax error near unexpected token '%c'\n", c);
		return (PARSE);
	}
	return (0);
}