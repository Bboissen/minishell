/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:24:01 by bboissen          #+#    #+#             */
/*   Updated: 2023/12/22 12:02:15 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long	n;
	int				i;
	int				sign;

	n = 0;
	i = 0;
	sign = 1;
	while (((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (int)(str[i] - '0');
		i++;
	}
	if (n > 9223372036854775807 && sign == 1)
		return (-1);
	else if (n > 9223372036854775807 && sign == -1)
		return (0);
	return ((int) n * sign);
}
