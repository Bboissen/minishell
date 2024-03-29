/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:57:26 by bboissen          #+#    #+#             */
/*   Updated: 2023/11/15 11:45:31 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			j = i;
		i++;
	}
	if (*(s + i) == (char)c)
		return ((char *)(s + i));
	if (j != -1)
		return ((char *)(s + j));
	return (NULL);
}
