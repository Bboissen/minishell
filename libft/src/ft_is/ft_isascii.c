/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:30:03 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 09:50:44 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the character is an ASCII character.
 * 
 * @param c The character to check.
 * @return {int} Returns non-zero if the character is an ASCII character,
 * and zero otherwise.
 */
int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}
