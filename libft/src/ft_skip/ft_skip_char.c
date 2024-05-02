/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:58:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:43:31 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Skips all occurences of the character 'c' in the string 'str'.
 * 
 * @param str The string to skip characters in.
 * @param i The index to start skipping from.
 * @param c The character to skip.
 */
void	ft_skip_char(const char *str, int *i, char c)
{
	while (str[*i] == c)
		(*i)++;
}
