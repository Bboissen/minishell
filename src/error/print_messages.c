/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:05:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/16 00:10:01 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a quit message with the given exit code.
 * 
 * @param code The exit code to print.
 */
void	print_quit_message(int signo)
{
	char	*nbr;

	nbr = ft_itoa(signo);
	ft_printfd(STDERR, "Quit: %s\n", nbr);
	ft_memdel(nbr);
}
