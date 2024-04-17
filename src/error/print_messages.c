/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:05:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/16 17:56:15 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a quit message with the given exit code.
 * 
 * @param code The exit code to print.
 */
void	print_sigquit_message(int code)
{
	char	*nbr;
	t_sig	*sig;

	sig = get_sig();
	if (sig->sig == 2)
	{
		nbr = ft_itoa(code);
		ft_printfd(STDERR, "Quit: %s\n", nbr);
		ft_memdel(nbr);
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}
