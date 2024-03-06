/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:53:26 by gdumas            #+#    #+#             */
/*   Updated: 2024/02/01 10:26:28 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	while (ft_strchr(set, (int)s1[start]))
		start++;
	end = ft_strlen(s1);
	while (ft_strchr(set, (int)s1[end]))
		end--;
	return (ft_substr(s1, start, (end - start) + 1));
}
