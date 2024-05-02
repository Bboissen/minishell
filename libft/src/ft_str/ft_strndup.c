/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:47:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:53:55 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates the string 'str' up to 'n' characters.
 * 
 * @param str The string to duplicate.
 * @param n The number of characters to duplicate.
 * @return {char *} The duplicated string.
 */
char	*ft_strndup(const char *str, int n)
{
	int		i;
	int		len;
	char	*out;

	len = 0;
	while (str[len])
		len++;
	if (n < len)
		len = n;
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
