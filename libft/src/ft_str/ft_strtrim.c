/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:53:26 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:55:22 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a copy of 's1' with
 * the characters specified in 'set' removed from the beginning
 * and the end of the string.
 * 
 * @param s1 The string to be trimmed.
 * @param set The set of characters to trim.
 * @return {char*} The trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	while (ft_strchr(set, (int)s1[start]))
		start++;
	end = ft_strlen(s1);
	while (ft_strchr(set, (int)s1[end]))
		end--;
	return (ft_substr(s1, start, (end - start) + 1));
}
