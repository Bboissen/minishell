/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:52:55 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:21:45 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the character c to the given file descriptor.
 * 
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 * @return {int} Returns the number of bytes written, or -1 on error.
 */
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
