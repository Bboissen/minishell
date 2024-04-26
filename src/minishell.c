/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/26 16:11:33 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief The main function of the program.
 * The function initializes minishell, then enters a loop where it 
 * reads a line from the terminal,
 * processes the line, executes the corresponding command(s), and then 
 * reinitializes the shell for the next line.
 * The loop continues until the shell is instructed to exit.
 * 
 * @param {int} ac - The count of command-line arguments.
 * @param {char**} av - The command-line arguments.
 * @param {char**} env - The environment for the shell.
 * @return {int} - Returns the status of the shell execution.
 */
int	main(int ac, char **av, char **env)
{
	t_mini	*mini;
	t_sig	*sig;

	if (ac != 1)
		return (ERROR);
	sig = get_sig();
	init_mini(&mini, env, av[0]);
	while (sig->exit == FALSE)
	{
		readline_setup(mini, &(mini->rl), mini->name);
		if (mini->rl == NULL)
			return (ft_printfd(STDERR_FILENO, "exit\n"), clean_exit(mini));
		lexer(mini);
		heredoc(mini);
		expand_join(&mini);
		if (mini->h_token)
			parser(mini);
		if (mini->cmd)
			cmd_exec(mini);
		reinit(&mini);
	}
	return (clean_exit(mini));
}
