/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:02:44 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/31 12:43:17 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formats(va_list	args, const char format)
{
	int	nprinted;

	nprinted = 0;
	if (format == 'c')
		nprinted += ft_printchar(va_arg(args, int));
	else if (format == 's')
		nprinted += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		nprinted += ft_printptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		nprinted += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		nprinted += ft_printunsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		nprinted += ft_printhex(va_arg(args, unsigned int), format);
	else if (format == '%')
		nprinted += write(1, "%", 1);
	return (nprinted);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		nprinted;
	int		i;

	nprinted = 0;
	i = 0;
	if (str == NULL || write(1, 0, 0) == -1)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			nprinted += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			nprinted += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (nprinted);
}
