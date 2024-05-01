/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/01 11:14:28 by bboissen         ###   ########.fr       */
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
	// int		i;

	if (ac != 1)
		return (ERROR);
	sig = get_sig();
	init_mini(&mini, env, av[0]); //protected random iteration
	while (sig->exit == FALSE)
	{
		readline_setup(mini, &(mini->rl), mini->name); //protected
		lexer(mini); //protected
		// mini->token = mini->h_token;
		// printf( "\n------------------------------------------\n");
		// printf("|type\t|%-20s|join|expand|\n", "string");
		// printf("------------------------------------------\n");
		// while (mini->token)
		// {
		// 	printf("|%d\t|%-20s|%-4d|%d|\n", mini->token->type, mini->token->str, mini->token->join, mini->token->expand);
		// 	mini->token = mini->token->next;
		// }
		// mini->token = mini->h_token;
		if (mini->token)
		{
			heredoc(mini); //protected random iteration
			expand_join(&mini);
		}
		if (mini->h_token)
			parser(mini);
		// printf("\n-----------------------------------------------\n");
		// printf("|%-20s\t|builtin|%-10s|%-10s|\n", "cmd", "infile", "outfile");
		// printf("-----------------------------------------------\n");
		// mini->cmd = mini->h_cmd;
		// while (mini->cmd)
		// {
		// 	i = 0;
		// 	if (mini->cmd->args)
		// 	{
		// 		while(mini->cmd->args[i])
		// 			printf("%s ", mini->cmd->args[i++]);
		// 		printf("%-5s ", " ");
		// 	}
		// 	else
		// 		printf("|%-10s\t|", "NULL");
		// 	printf("|%-7d|%-10s|%-10s|\n", mini->cmd->builtin, mini->cmd->in, mini->cmd->out);
		// 	mini->cmd = mini->cmd->next;
		// }
		// ft_printfd(1,"\n\n");
		mini->cmd = mini->h_cmd;
		mini->env = mini->h_env;
		if (mini->cmd)
			cmd_exec(mini);
		reinit(&mini);
	}
	return (clean_exit(mini));
}
