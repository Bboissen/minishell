/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:02:43 by bboissen          #+#    #+#             */
/*   Updated: 2023/11/15 12:09:25 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void		*ptr;
	size_t		i;

	i = 0;
	if (nelem * elsize > 4294967295)
		return (NULL);
	ptr = malloc(nelem * elsize);
	if (!ptr)
		return (NULL);
	while (i < nelem * elsize)
	{
		((unsigned char *) ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
