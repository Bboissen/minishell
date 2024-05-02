/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:47:31 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:49:03 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares the two strings 's1' and 's2'.
 * 
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return {int} An integer less than, equal to,
 * or greater than zero if 's1' is found, respectively, to be less than,
 * to match, or be greater than 's2'.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	i = 0;
	while (b1[i] || b2[i])
	{
		if (b1[i] != b2[i])
			return (b1[i] - b2[i]);
		i++;
	}
	return (SUCCESS);
}
