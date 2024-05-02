/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:37:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:50:01 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares the strings 's1' and 's2'.
 * 
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return {int} TRUE if the strings are equal, FALSE otherwise.
 */
int	ft_strequ(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (!ft_strcmp(s1, s2))
		return (TRUE);
	else
		return (FALSE);
}
