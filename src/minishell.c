/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/01 16:29:19 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO
//unset seems to delete the newly attributed env
// exec issue when
// <test2 ls | ls >test2 | ls | ls

// ls | grep Makefile | ls

// <test cat | grep s

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

// TOFIX
// -----export------
// not a valid identifier: wrong error code
// issue with "export ="

// -----unset------
// "unset" wrong error code

// -----cd------
// no error code

// -----exit------
// no error code
// CTRL+D not exiting when executing folder ./tester

// -----parser------
// no such file or directory: wrong error code
// if directory to exec, error code
// manage with errno and strerror -> see parser error

// -----signal------
// "^C^C" when sleep 5

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
		lexer(mini);
		if (mini->token)
		{
			heredoc(mini);
			expand_join(&mini);
		}
		if (mini->h_token)
			parser(mini);
		if (mini->cmd)
			cmd_exec(mini);
		reinit(&mini);
	}
	return (clean_exit(mini));
}
