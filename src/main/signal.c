/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/26 16:46:41 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a quit message with the given exit code.
 * 
 * @param code The exit code to print.
 */
static void	print_quit_message(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	ft_printfd(STDERR, "Quit: %s\n", nbr);
	ft_memdel(nbr);
}

/**
 * @brief Handles the SIGINT signal.
 * 
 * @param mini The main structure of the program.
 * @param code The signal code.
 */
void	sig_int(t_mini *mini, int code)
{
	(void)code;
	if (mini->sig.pid == 0)
	{
		ft_printfd(STDERR, "\b\b  \n\033[0;36m\033[1m🤬 minishell ▸ \033[0m");
		mini->sig.status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		mini->sig.status = 130;
	}
	mini->sig.sigint = 1;
}

/**
 * @brief Handles the SIGQUIT signal.
 * 
 * @param mini The main structure of the program.
 * @param code The signal code.
 */
void	sig_quit(t_mini *mini, int code)
{
	if (mini->sig.pid != 0)
	{
		print_quit_message(code);
		mini->sig.status = 131;
		mini->sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}

/**
 * @brief Initializes the signal handling structure.
 * 
 * @param mini The main structure of the program.
 */
void	sig_init(t_mini *mini)
{
	mini->sig.sigint = 0;
	mini->sig.sigquit = 0;
	mini->sig.status = 0;
	mini->sig.exit = 0;
	mini->sig.pid = 0;
}
