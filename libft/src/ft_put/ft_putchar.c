/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:52:53 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:21:54 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the character c to the standard output.
 * 
 * @param c The character to output.
 */
void	ft_putchar(char c)
{
	write(1, &c, 1);
}
