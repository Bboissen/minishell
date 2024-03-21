/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:25 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/15 16:09:48 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);
}

void	print_quit_message(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	ft_putstr_fd("Quit: ", STDERR);
	ft_putendl_fd(nbr, STDERR);
	ft_memdel(nbr);
}

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		print_prompt();
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	if (g_sig.pid != 0)
	{
		print_quit_message(code);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
