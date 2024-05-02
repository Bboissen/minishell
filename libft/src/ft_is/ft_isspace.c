/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:01:16 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:05:18 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the character is a space character.
 * 
 * @param c The character to check.
 * @return {int} Returns non-zero if the character is a space character,
 * and zero otherwise.
 */
int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}
