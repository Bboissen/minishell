/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:34:17 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/22 16:17:47 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_err(int err, char c)
{
	if (err == QUOTE)
	{
		dprintf(STDERR_FILENO, "minishell: odd number of quotes\n");
		return (QUOTE);
	}
	else if(err == PARSE)
	{
		dprintf(STDERR_FILENO, "minishell: syntax error near unexpected token '%c'\n", c);
		return (PARSE);
	}
	return (0);
}