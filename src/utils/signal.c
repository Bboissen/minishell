/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 15:46:40 by gdumas           ###   ########.fr       */
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

/*crtl-c*/
/**
 * @brief Handles the SIGINT signal.
 * 
 * @param mini The main structure of the program.
 * @param code The signal code.
 */
void	sig_int(t_mini *mini, int signo)
{
	(void)signo;
	if (mini->cmd->pid == 0)
	{
		mini->sig.status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		mini->sig.status = INTERUPT;
	}
	mini->sig.sigint = 1;
}

/*crtl-\*/
/**
 * @brief Handles the SIGQUIT signal.
 * 
 * @param mini The main structure of the program.
 * @param code The signal code.
 */
void	sig_quit(t_mini *mini, int signo)
{
	print_quit_message(signo);
	mini->sig.status = QUIT;
	mini->sig.sigquit = 1;
	while (mini->cmd->pid != 0)
	{
		kill(mini->cmd->pid, SIGKILL);
		mini->cmd = mini->cmd->next;
	}
	ft_putstr_fd("\b\b  \b\b", STDERR);
}

/**
 * @brief Initializes the signal handling structure.
 * 
 * @param mini The main structure of the program.
 */
void	sig_init(t_mini *mini)
{
	mini->sig.status = 0;
	mini->sig.sigint = 0;
	mini->sig.sigquit = 0;
	mini->sig.exit = 0;
}
