/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:46:29 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/26 15:10:53 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles quotes in a given line of text.
 * 
 * @param line The line of text to process.
 * @param i Pointer to the current index in the line.
 * @param j Pointer to the current position in the line.
 * @param c Pointer to the current character being processed.
 * @return int The count of quotes handled.
 */
int	handle_quotes(char *line, int *i, int *j, char *c)
{
	int	count;

	count = 0;
	if (*c == ' ' && (line[*i + *j] == '\'' || line[*i + *j] == '\"'))
		*c = line[*i + (*j)++];
	else if (*c != ' ' && line[*i + *j] == *c)
	{
		count += 2;
		*c = ' ';
		(*j)++;
	}
	else
		(*j)++;
	return (count);
}
