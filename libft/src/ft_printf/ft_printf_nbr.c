/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:21:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/31 12:43:34 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_itoa(n);
	i = ft_printstr(num);
	free(num);
	return (i);
}

int	ft_numlen(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	if (n == 0)
	{
		num = (char *)malloc(sizeof(char) * 2);
		if (!num)
			return (0);
		num[0] = '0';
		num[1] = '\0';
		return (num);
	}
	len = ft_numlen(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len] = '\0';
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

int	ft_printunsigned(unsigned int n)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_uitoa(n);
	i = ft_printstr(num);
	free(num);
	return (i);
}
