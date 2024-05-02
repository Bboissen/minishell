/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:29:22 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:57:50 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory for the string representation of an integer.
 * 
 * @param len The length of the string representation of an integer.
 * @return A pointer to the allocated string,
 * or NULL if memory allocation fails.
 */
static char	*pre_conv(int len)
{
	char	*tmp;

	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '0';
	return (tmp);
}

/**
 * @brief Calculates the length of the string representation of an integer.
 * 
 * This function takes an integer as input and returns the length of its string
 * representation. If the integer is negative,
 * it adds one to the length to account for the minus sign.
 * 
 * @param nbr The integer to calculate the length of its string representation.
 * @return The length of the string representation of the integer.
 */
static int	int_len(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

/**
 * @brief Converts an integer to a string.
 * 
 * @param n The integer to convert to a string.
 * @return {char *} A pointer to the string representation of the integer,
 * or NULL if memory allocation fails.
 */
char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*result;
	long	nbr;

	nbr = n;
	len = int_len(nbr);
	result = pre_conv(len);
	if (!result)
		return (NULL);
	if (nbr < 0)
		nbr = -nbr;
	i = len - 1;
	while (nbr != 0)
	{
		result[i] = ((nbr % 10) + '0');
		nbr = nbr / 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	result[len] = 0;
	return (result);
}
