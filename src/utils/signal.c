/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/06 11:12:41 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the signal handling.
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

/**
 * @brief Signal handler for SIGINT and SIGQUIT signals.
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
 * @brief Retrieves a pointer to a static t_sig instance.
 * To create a singleton.
 *
 * @return Pointer to the static t_sig instance.
 */
t_sig	*get_sig(void)
{
	static t_sig	sig;

	return (&sig);
}
