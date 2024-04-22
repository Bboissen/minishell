/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/22 17:19:25 by gdumas           ###   ########.fr       */
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
		ft_putstr_fd("^C\n", STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (code == SIGQUIT)
	{
		if (sig->working == TRUE)
		{
			sig->status = QUIT;
			ft_printfd(STDERR_FILENO, "Quit  (core dumped)\n");
		}
	}
}

/**
 * @brief Initializes the signal handling structure.
 * 
 * @param mini The main structure of the program.
 */
void	sig_init(void)
{
	int		i;
	t_sig	*sig;

	sig = get_sig();
	sig->status = SUCCESS;
	sig->working = FALSE;
	sig->exit = FALSE;
	i = 0;
	while (i < _NSIG)
		signal(i++, SIG_IGN);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_catch_signals = 0;
}
