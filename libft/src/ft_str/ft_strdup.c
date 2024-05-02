/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:47:19 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:51:01 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates sufficient memory for a copy of the string 'str',
 * does the copy, and returns a pointer to it.
 * 
 * @param str The string to copy.
 * @return {char *} A pointer to the copy of the string.
 */
char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*out;

	len = 0;
	while (str[len])
		len++;
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
