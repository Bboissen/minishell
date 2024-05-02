/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:17:44 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:55:07 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Extracts tokens from strings.
 * 
 * @param str The string to tokenize.
 * @param delim The delimiter character.
 * @return {char *} A pointer to the next token,
 * or NULL if there are no more tokens.
 */
char	*ft_strtok(char *str, char delim)
{
	static char	*token;
	char		*start;

	if (str)
		token = str;
	if (!token)
		return (NULL);
	while (*token == delim)
		token++;
	if (!*token)
	{
		token = NULL;
		return (NULL);
	}
	start = token;
	while (*token && *token != delim)
		token++;
	if (*token)
	{
		*token = '\0';
		token++;
	}
	return (start);
}
