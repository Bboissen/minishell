/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:24:43 by bboissen          #+#    #+#             */
/*   Updated: 2024/03/19 11:45:55 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_test_base(char *str)
{
	int	i;
	int	j;
	int	r;

	i = 0;
	j = 0;
	r = 1;
	while (str[i])
	{
		if ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
			r = 0;
		else if (str[i] == '+' || str[i] == '-')
			r = 0;
		while (j < i)
		{
			if (str[j] == str[i])
				r = 0;
			j++;
		}
		j = 0;
		i++;
	}
	return (r);
}

static int	ft_ulong_base(int fd,
unsigned long long nb, char *str, unsigned int l_base)
{
	char			c;
	static int		count;
	int				check;

	count = 0;
	c = str[nb % l_base];
	if (nb >= l_base)
		ft_ulong_base(fd, nb / l_base, str, l_base);
	check = write (fd, &c, 1);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}

static int	ft_int_base(int fd,
unsigned int nb, char *str, unsigned int len_base)
{
	char			c;
	static int		count;
	int				check;

	count = 0;
	c = str[nb % len_base];
	if (nb >= len_base)
		ft_int_base(fd, nb / len_base, str, len_base);
	check = write (fd, &c, 1);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}

int	ft_putnbr_base(int fd, unsigned long long nbr, char *base, char c)
{
	int	n;

	n = ft_strlen(base);
	if (n > 1 && ft_test_base(base))
	{
		if (c == 'i' || c == 'd')
			return (ft_int_base(fd, nbr, base, n));
		else if (c == 'u' || c == 'p' || c == 'x' || c == 'X')
			return (ft_ulong_base(fd, nbr, base, n));
	}
	return (0);
}
