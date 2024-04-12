/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:05:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/12 12:05:53 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a quit message with the given exit code.
 * 
 * @param code The exit code to print.
 */
static void	print_quit_message(int signo)
{
	char	*nbr;

	nbr = ft_itoa(signo);
	ft_printfd(STDERR, "Quit: %s\n", nbr);
	ft_memdel(nbr);
}
