/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/17 16:22:44 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int code)
{
	t_sig	*sig;

	sig = get_sig();
	if (code == SIGINT)
	{
		sig->status = INTERUPT;
		sig->sig = 1;
		ft_putstr_fd("\n", STDERR);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (code == SIGQUIT)
	{
		sig->status = QUIT;
		//print_sigquit_message(code);
		sig->sig = 1;
	}
}

/**
 * @brief Initializes the signal handling structure.
 * 
 * @param mini The main structure of the program.
 */
void	sig_init(void)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = 0;
	sig->sig = 0;
	sig->exit = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
