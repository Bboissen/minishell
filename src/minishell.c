/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 17:28:14 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The main function of the shell.
 * @param {int} ac - The count of command-line arguments.
 * @param {char**} av - The command-line arguments.
 * @param {char**} env - The environment for the shell.
 * @return {int} - Returns the status of the shell execution.
 * The function initializes the shell, then enters a loop where it 
 * reads a line from the terminal,
 * processes the line, executes the corresponding command, and then 
 * reinitializes the shell for the next line.
 * The loop continues until the shell is instructed to exit.
 */
int	main(int ac, char **av, char **env)
{
	t_mini	*mini;
	char	*rl;

	rl = NULL;
	mini = NULL;
	if (ac != 1)
		return (ERROR);
	init_mini(&mini, env, av[0]);
	/*printf("%s\n", mini->name);
	while (mini->env)
	{
		printf("%s=%s\n", mini->env->name, mini->env->value);
		mini->env = mini->env->next;
	}
	printf("%d\n", mini->sig.status);
	printf("%d\n", mini->sig.sigint);
	printf("%d\n", mini->sig.sigquit);
	printf("%d\n", mini->sig.exit);*/
	while (!mini->sig.exit)
	{
		readline_setup(rl, av[0]);
		/*heredoc(mini);
		lexer(mini, rl);
		expand_join(mini);
		parser(mini);
		if (mini->cmd)
			exec_cmd(mini);*/
		reinit(mini, rl);
	}
	return (clean_exit(mini));
}
