/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:24:24 by bboissen          #+#    #+#             */
/*   Updated: 2023/11/15 12:17:36 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nc;
	char			a;

	if (n < 0)
	{
		nc = -n;
		write(fd, "-", 1);
	}
	else
		nc = n;
	a = nc % 10 + '0';
	if (nc >= 10)
	{
		ft_putnbr_fd(nc / 10, fd);
	}
	write(fd, &a, 1);
}
