/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 12:58:13 by gdumas           ###   ########.fr       */
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
 * @param {int} ac - The count of command-line arguments.
 * @param {char**} av - The command-line arguments.
 * @param {char**} env - The environment for the shell.
 * @return {int} - Returns the status of the shell execution.
 */
int	main(int ac, char **av, char **env)
{
	t_mini	*mini;
	t_sig	*sig;
	int		err;
	// int		i;

	if (ac != 1)
		return (ERROR);
	sig = get_sig();
	init_mini(&mini, env, av[0]);
	while (sig->exit == FALSE)
	{
		err = 0;
		readline_setup(mini, &(mini->rl), mini->name);
		lexer(mini);
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
			heredoc(mini);
		if (mini->token)
			expand_join(&mini);
		if (mini->h_token)
			err = parser(mini);
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
		// mini->cmd = mini->h_cmd;
		// mini->env = mini->h_env;
		if (mini->cmd)
			cmd_exec(mini);
		if (err != 0)
			get_sig()->status = err;
		reinit(&mini);
	}
	return (clean_exit(mini));
}
