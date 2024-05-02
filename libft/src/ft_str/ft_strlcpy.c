/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:47:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:52:13 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies up to 'dstsize' characters from the string 'src' to 'dest'.
 * 
 * @param dest The destination string.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return {size_t} The length of the source string.
 */
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	unsigned int	len;
	size_t			i;

	len = 0;
	while (src[len] != '\0')
		len++;
	if (dstsize == 0)
		return (len);
	i = 0;
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
