/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:53:15 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:50:56 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of 's1' and 's2'.
 * 
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return {char *} The new string. NULL if the allocation fails.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*out;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
	{
		if (!(s1))
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	out = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, s1, s1_len + 1);
	ft_strlcat(out + (s1_len), s2, s2_len + 1);
	return (out);
}
