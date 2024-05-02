/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:50:15 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:11:47 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies bytes from a source to a destination until a certain byte is
 * encountered.
 * 
 * @param dst The destination to copy to.
 * @param src The source to copy from.
 * @param c The byte to stop copying at.
 * @param n The number of bytes to copy.
 * @return {void *} Returns a pointer to the byte after the byte that caused
 * the copying to stop, or NULL if the byte was not found.
 */
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*q;

	i = 0;
	p = (unsigned char *)dst;
	q = (unsigned char *)src;
	while (i < n)
	{
		p[i] = q[i];
		if (q[i] == c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
