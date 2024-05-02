/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:54:53 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 09:51:19 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the occurrences of a character in a string.
 * 
 * @param c The character to count.
 * @param base The string in which to count the character.
 * @return {int} Returns the count of the character in the string.
 */
int	ft_iscount(int c, char *base)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			count++;
		i++;
	}
	return (count);
}
