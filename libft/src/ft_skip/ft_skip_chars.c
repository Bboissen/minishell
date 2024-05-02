/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:58:46 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:43:42 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Skips all occurences of characters in
 * the string 'base' in the string 'str'.
 * 
 * @param str The string to skip characters in.
 * @param i The index to start skipping from.
 * @param base The characters to skip.
 */
void	ft_skip_chars(const char *str, int *i, char *base)
{
	while (ft_isin(str[*i], base))
		(*i)++;
}
