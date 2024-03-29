/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:23 by bboissen          #+#    #+#             */
/*   Updated: 2023/11/15 12:49:24 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				sign;
	unsigned int	nb;

	i = size(n);
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		nb = -n;
	}
	else
		nb = n;
	str = malloc((i + 1 + sign) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-';
	str[i + sign] = '\0';
	while (i-- > 0)
	{
		str[i + sign] = '0' + nb % 10;
		nb /= 10;
	}
	return (str);
}
