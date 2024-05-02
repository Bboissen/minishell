/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:24:43 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/02 10:29:18 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Tests if a string is a valid base.
 * 
 * @param str The string to test.
 * @return {int} Returns 1 if the string is a valid base, and 0 otherwise.
 */
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

/**
 * @brief Writes an unsigned long long number
 * to a file descriptor in a given base.
 * 
 * @param fd The file descriptor to write to.
 * @param nb The number to write.
 * @param str The base to write the number in.
 * @param l_base The length of the base.
 * @return {int} Returns the number of bytes written,
 * or -1 if an error occurred.
 */
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

/**
 * @brief Writes an unsigned int number to a
 * file descriptor in a given base.
 * 
 * @param fd The file descriptor to write to.
 * @param nb The number to write.
 * @param str The base to write the number in.
 * @param len_base The length of the base.
 * @return {int} Returns the number of bytes written,
 * or -1 if an error occurred.
 */
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

/**
 * @brief Writes a number to a file descriptor in a given base.
 * 
 * @param fd The file descriptor to write to.
 * @param nbr The number to write.
 * @param base The base to write the number in.
 * @param c The format character.
 * @return int Returns the number of bytes written,
 * or FALSE if the base is not valid.
 */
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
	return (FALSE);
}
