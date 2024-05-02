/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:39:32 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 14:40:25 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the string 'str' to the given file descriptor,
 * followed by a newline.
 * 
 * @param str The string to output.
 * @param fd The file descriptor on which to write.
 * @return {int} The number of characters written.
 */
int	ft_putendl_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	i += write(fd, "\n", 1);
	return (i);
}
