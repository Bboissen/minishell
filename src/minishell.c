/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 14:20:28 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief The main function of the program.
 * 
 * The function initializes minishell, then enters a loop where it 
 * reads a line from the terminal,
 * processes the line, executes the corresponding command(s), and then 
 * reinitializes the shell for the next line.
 * The loop continues until the shell is instructed to exit.
 * 
 * @param ac The count of command-line arguments.
 * @param av The command-line arguments.
 * @param env The environment for the shell.
 * @return {int} - Returns the status of the shell execution.
 */
int	main(int ac, char **av, char **env)
{
	t_mini	*mini;
	int		err;

	if (ac != 1)
		return (ERROR);
	err = 0;
	init_mini(&mini, env, av[0]);
	while (get_sig()->exit == FALSE)
	{
		err = 0;
		readline_setup(mini, &(mini->rl), mini->name);
		lexer(mini);
		if (mini->h_token)
			heredoc(mini);
		if (mini->h_token)
			expand_join(&mini);
		if (mini->h_token)
			err = parser(mini);
		if (mini->h_cmd)
			cmd_exec(mini);
		if (err != 0)
			get_sig()->status = err;
		reinit(&mini);
	}
	return (clean_exit(mini));
}
