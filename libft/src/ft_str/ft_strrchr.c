/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:17:37 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:54:58 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of 'c' in the string 's'.
 * 
 * @param s The string to search.
 * @param c The character to search for.
 * @return {char *} A pointer to the located character,
 * or NULL if the character does not appear in the string.
 */
char	*ft_strrchr(char *s, int c)
{
	char	*last;
	char	find;
	int		i;

	last = (char *)s;
	find = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (last[i] == find)
			return (last + i);
		i--;
	}
	return (NULL);
}
