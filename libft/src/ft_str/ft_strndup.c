/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:07:44 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/08 18:19:51 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int n)
{
	int		i;
	char	*out;

	out = (char *)malloc(sizeof(char) * (n + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (str[i] || i < n)
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
