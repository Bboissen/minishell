/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:21:30 by bboissen          #+#    #+#             */
/*   Updated: 2024/02/07 15:09:11 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_FD_H
# define PRINTF_FD_H

# include <unistd.h>
# include <stdarg.h>

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		seq_write(int fd, char *s, int len);
int		printf_fd(int fd, const char *format, ...);
int		converter(int fd, char c, va_list ptr);
int		ft_putstr_fd(char *s, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putnbr_base(int fd, unsigned long long nbr, char *base, char c);

#endif