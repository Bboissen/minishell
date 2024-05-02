/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:30:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:03:41 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the character is a digit.
 * 
 * @param c The character to check.
 * @return {int} Returns non-zero if the character is a digit,
 * and zero otherwise.
 */
int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}
