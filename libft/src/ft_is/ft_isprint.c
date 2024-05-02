/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:42:43 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:05:01 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the character is printable.
 * 
 * @param c The character to check.
 * @return {int} Returns non-zero if the character is printable,
 * and zero otherwise.
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (c);
	return (FALSE);
}
