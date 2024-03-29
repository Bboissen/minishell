/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:02:12 by bboissen          #+#    #+#             */
/*   Updated: 2024/01/29 16:56:27 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_array(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static int	count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
		else
		{
			while (*s && *s == c)
				s++;
		}
	}
	return (words);
}

static char	**filler(char const *s, char **arr, int end, int i)
{
	arr[i] = ft_substr(s, 0, end);
	if (!arr[i])
	{
		free_array(arr, i);
		return (NULL);
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		j;
	char	**arr;

	i = -1;
	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (arr == NULL || !s)
		return (NULL);
	while (++i < words)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (*(s + j) && *(s + j) != c)
			j++;
		arr = filler(s, arr, j, i);
		if (!arr)
			return (NULL);
		s += j;
	}
	arr[i] = NULL;
	return (arr);
}
