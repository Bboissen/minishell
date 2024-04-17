/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/17 11:25:16 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The main function of the program.
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
	char	*rl;

	rl = NULL;
	mini = NULL;
	if (ac != 1)
		return (ERROR);
	sig = get_sig();
	init_mini(&mini, env, av[0]);
	while (!sig->exit)
	{
		readline_setup(&rl, mini->name);
		// heredoc(mini);
		// lexer(mini, rl);
		// expand_join(mini);
		// parser(mini);
		if (mini->cmd)
			cmd_exec(mini);
		reinit(mini, rl);
	}
	return (clean_exit(mini));
}

/*printf("%s\n", mini->name);
	while (mini->env)
	{
		printf("%s=%s\n", mini->env->name, mini->env->value);
		mini->env = mini->env->next;
	}
	env = h_env
	printf("%d\n", mini->sig.status);
	printf("%d\n", mini->sig.sig);
	printf("%d\n", mini->sig.exit);
	print_sorted_env(mini->h_env);*/