/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:16:18 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/02 10:21:10 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes a string to a file descriptor.
 * 
 * @param fd The file descriptor to write to.
 * @param s The string to write.
 * @param len The length of the string.
 * @return {int} Returns the number of bytes written,
 * or -1 if an error occurred.
 */
static int	seq_write(int fd, char *s, int len)
{
	return (write(fd, s, len));
}

/**
 * @brief Converts a format string and writes it to a file descriptor.
 * 
 * @param fd The file descriptor to write to.
 * @param count A pointer to the count of characters written.
 * @param ptr The variable argument list containing the values to convert.
 * @param format The format string to convert.
 * @return {char*} Returns a pointer to the next character in the format string.
 */
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

/**
 * @brief Parses a format string and writes it to a file descriptor.
 * 
 * @param fd The file descriptor to write to.
 * @param ptr The variable argument list containing the values to convert.
 * @param format The format string to parse.
 * @return int Returns the count of characters written,
 * or -1 if an error occurred.
 */
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

/**
 * @brief Writes a formatted string to a file descriptor.
 * 
 * @param fd The file descriptor to write to.
 * @param format The format string to write.
 * @param ... The values to write.
 * @return int Returns the count of characters written,
 * or -1 if an error occurred.
 */
int	ft_printfd(int fd, const char *format, ...)
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
