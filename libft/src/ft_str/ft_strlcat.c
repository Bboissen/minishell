/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:47:22 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:52:06 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends the NUL-terminated string 'src' to the end of 'dest'.
 * It will append at most 'dstsize - strlen(dest) - 1' characters.
 * It will then NUL-terminate, unless 'dstsize'
 * is 0 or the original 'dest' string was longer than 'dstsize'.
 * 
 * @param dest The destination string.
 * @param src The source string.
 * @param dstsize The size of the destination buffer.
 * @return {size_t} The total length of the string it tried to create.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize < dst_len + 1)
		return (dstsize + src_len);
	if (dstsize > dst_len + 1)
	{
		while (src[i] != '\0' && dst_len + 1 + i < dstsize)
		{
			dest[dst_len + i] = src[i];
			i++;
		}
	}
	dest[dst_len + i] = '\0';
	return (dst_len + src_len);
}
