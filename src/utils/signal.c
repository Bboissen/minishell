/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 11:40:44 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Signal handler for SIGINT and SIGQUIT signals.
 * 
 * This function is called when a SIGINT or SIGQUIT signal is received.
 * It updates the status of the signal and prints a message to 
 * the standard error.
 * 
 * @param code The signal code. Can be either SIGINT or SIGQUIT.
 */
void	sig_handler(int code)
{
	t_sig	*sig;

	sig = get_sig();
	if (code == SIGINT)
	{
		sig->status = INTERUPT;
		if (sig->working == FALSE)
			ft_putstr_fd("^C", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (sig->working != TRUE)
			rl_redisplay();
	}
	else if (code == SIGQUIT)
	{
		if (sig->working == TRUE)
		{
			sig->status = QUIT;
			ft_printfd(STDERR_FILENO, "Quit (core dumped)\n");
		}
		else
			return ;
	}
}

/**
 * @brief Initializes the signal handling.
 * 
 * This function initializes the signal handling by setting the default status 
 * and ignoring all signals except SIGINT and SIGQUIT, 
 * which are handled by sig_handler.
 */
void	sig_init(void)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = SUCCESS;
	sig->working = FALSE;
	sig->exit = FALSE;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
}
