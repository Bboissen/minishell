/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:56:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:05:44 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the index of the character in the string.
 * 
 * @param c The character to find.
 * @param base The string in which to find the character.
 * @return {int} Returns the index of the character in the string,
 * or -1 if the character is not found.
 */
int	ft_iswhere(int c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
