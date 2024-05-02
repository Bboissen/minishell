/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:55:18 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:04:42 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the character is in the string.
 * 
 * @param c The character to check.
 * @param base The string in which to check the character.
 * @return {int} Returns non-zero if the character is in the string,
 * and zero otherwise.
 */
int	ft_isin(int c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
