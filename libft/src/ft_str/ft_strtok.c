/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:17:44 by gdumas            #+#    #+#             */
/*   Updated: 2024/01/30 14:57:35 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtok(char **av)
{
	static char	*buffer;
	char		*token;
	int			i;

	buffer = av[1];
	if (av[1] && (*buffer != '\0'))
	{
		token = buffer;
		i = 1;
		while (*buffer)
		{
			if (*buffer == ' ')
			{
				*buffer = '\0';
				av[i++] = token;
				token = buffer + 1;
			}
			buffer++;
		}
		if (buffer != token || *buffer != '\0')
			av[i++] = token;
		av[i] = NULL;
	}
	else
		exit(0);
}
