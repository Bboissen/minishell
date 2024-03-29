/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:36:57 by bboissen          #+#    #+#             */
/*   Updated: 2023/11/15 12:50:21 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strsrch(char const *s, int step, int len, char const *set)
{
	int	i;
	int	j;

	i = 0;
	if (step < 0)
		i = len - 1;
	while (s[i])
	{
		j = -1;
		while (set[++j])
		{
			if (s[i] == set[j])
				break ;
		}
		if (s[i] != set[j])
			break ;
		i += step;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trim;
	int			len;
	int			start;
	size_t		len_trim;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	start = strsrch(s1, 1, len, set);
	len_trim = strsrch(s1, -1, len, set) - start + 1;
	trim = ft_substr(s1, start, len_trim);
	return (trim);
}
