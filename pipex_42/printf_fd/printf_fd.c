/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:16:18 by bboissen          #+#    #+#             */
/*   Updated: 2023/12/22 11:54:27 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

static char	*convert_check(int fd, int *count, va_list	ptr, const char *format)
{
	int	check;

	format++;
	check = converter(fd, *format++, ptr);
	if (check == -1)
		*count = -1;
	else if (check == -2)
	{
		format -= 2;
		check = seq_write(fd, (char *)format, 2);
		if (check == -1)
			*count = -1;
		format += 2;
		*count += check;
	}
	else
		*count += check;
	return ((char *) format);
}

static int	parsing(int fd, va_list	ptr, const char *format)
{
	int	i;
	int	count;
	int	check;

	count = 0;
	i = 0;
	while (format[i])
	{
		while (format[i] != '\0' && format[i] != '%')
			i++;
		check = seq_write(fd, (char *)format, i);
		if (check < 0)
			return (-1);
		count += check;
		format += i;
		if (*format == '%')
		{
			format = convert_check(fd, &count, ptr, format);
			if (count == -1)
				return (-1);
		}
		i = 0;
	}
	return (count);
}

int	printf_fd(int fd, const char *format, ...)
{
	int		count;
	int		check;
	va_list	ptr;

	count = 0;
	if (!format)
		return (-1);
	else if (!ft_strchr(format, '%'))
		return (ft_putstr_fd((char *) format, 1));
	else
	{
		va_start(ptr, format);
		check = parsing(fd, ptr, format);
		if (check == -1)
			return (-1);
		count += check;
	}
	va_end(ptr);
	return (count);
}
