/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/16 15:56:22 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_mini	*get_mini(void)
// {
// 	static t_mini	*mini;

// 	mini = NULL;
// 	if (mini == NULL)
// 	{
// 		mini = malloc(sizeof(t_mini));
// 		if (mini == NULL)
// 			exit(ERROR);
// 	}
// 	return (mini);
// }

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
	char	*rl;

	rl = NULL;
	// mini = get_mini();
	if (ac != 1)
		return (ERROR);
	init_mini(&mini, env, av[0]);
	while (!mini->sig.exit)
	{
		readline_setup(&rl, mini->name);
		lexer(mini, rl);
		heredoc(mini);
		expand_join(&mini);

		printf("\n------------------------------------------\n");
		printf("|type\t|%-20s|join|expand|\n", "string");
		printf("------------------------------------------\n");
		mini->token	= mini->h_token;
		while (mini->token)
		{
			dprintf(1, "|%d\t|%-20s|%-4d|%d|\n", mini->token->type, mini->token->str, mini->token->join, mini->token->expand);
			mini->token = mini->token->next;
		}
		parser(mini);
		getchar();
		// printf("\n------------------------------------------\n");
		// printf("|cmd\t|builtin|infile|outfile|\n");
		// printf("------------------------------------------\n");
		// mini->cmd	= mini->h_cmd;
		// while (mini->cmd)
		// {
		// 	dprintf(1, "|%s\t|%d|%s|%s|\n", mini->cmd->args[0], mini->cmd->builtin, mini->cmd->in, mini->cmd->out);
		// 	mini->token = mini->token->next;
		// }

		//if (mini->cmd)
		//	exec_cmd(mini);
		// reinit(mini, rl);
	}
	return (clean_exit(mini));
}

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