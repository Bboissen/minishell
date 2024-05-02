/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:17:44 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/26 09:09:01 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
