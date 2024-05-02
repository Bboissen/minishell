/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:02:23 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:10:40 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the absolute value of a number.
 * 
 * @param n The number to get the absolute value of.
 * @return {long} Returns the absolute value of the number.
 */
int	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
