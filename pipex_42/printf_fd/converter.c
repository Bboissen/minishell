/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:06:32 by bboissen          #+#    #+#             */
/*   Updated: 2023/12/22 11:54:32 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

static int	str_to_print(int fd, va_list ptr)
{
	char	*str;

	str = va_arg(ptr, char *);
	if (str)
		return (ft_putstr_fd(str, fd));
	else
		return (ft_putstr_fd("(null)", fd));
}

static int	ptr_to_print(int fd, va_list ptr, char c)
{
	char				*base;
	unsigned long long	addr;
	int					check;
	int					count;

	count = 0;
	base = "0123456789abcdef";
	addr = (unsigned long long) va_arg(ptr, unsigned long long);
	if (addr)
	{
		check = ft_putstr_fd("0x", fd);
		if (check == -1)
			return (-1);
		count += check;
		check = ft_putnbr_base(fd, addr, base, c);
		if (check == -1)
			return (-1);
		count += check;
		return (count);
	}
	else
		return (ft_putstr_fd("(nil)", fd));
}

static int	uint_to_print(int fd, va_list ptr, char *base, char c)
{
	unsigned int	nbr;

	nbr = (unsigned int) va_arg(ptr, int);
	return (ft_putnbr_base(fd, nbr, base, c));
}

static int	int_to_print(int fd, va_list ptr, char *base, char c)
{
	int	count;
	int	nbr;
	int	check;

	count = 0;
	nbr = va_arg(ptr, int);
	if (nbr < 0)
	{
		nbr *= -1;
		check = write (1, "-", 1);
		if (check == -1)
			return (-1);
		count += check;
	}
	check = ft_putnbr_base(fd, nbr, "0123456789", c);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}

int	converter(int fd, char c, va_list ptr)
{
	if (c == 'd' || c == 'i')
		return (int_to_print(fd, ptr, "0123456789", c));
	else if (c == 'u')
		return (uint_to_print(fd, ptr, "0123456789", c));
	else if (c == 'x')
		return (uint_to_print(fd, ptr, "0123456789abcdef", c));
	else if (c == 'X')
		return (uint_to_print(fd, ptr, "0123456789ABCDEF", c));
	else if (c == 'c')
		return (ft_putchar_fd(va_arg(ptr, int), fd));
	else if (c == '%')
		return (ft_putchar_fd('%', fd));
	else if (c == 'p')
		return (ptr_to_print(fd, ptr, c));
	else if (c == 's')
		return (str_to_print(fd, ptr));
	else if (c == '\0')
		return (-1);
	return (-2);
}
