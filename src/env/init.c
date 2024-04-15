/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:04:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 14:58:58 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets up and reads a line from the terminal with a custom prompt.
 * @param {char*} rl - The string to store the read line.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char*} str - The string to be used as the base of the prompt.
 * The function joins 'str' and " > " to create the prompt, 
 * reads a line from the terminal,
 * adds the line to the history, and then frees the prompt string.
 */
void	readline_setup(char *rl, t_mini *mini, char *str)
{
	char	*prompt;

	prompt = ft_strjoin(str, " > ");
	if (!prompt)
		exit(MALLOC);
	rl = readline(prompt);
	add_history(rl);
	rl_on_new_line();
	free(prompt);
}

/**
 * Initialize the mini structure with the given environment.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char**} env - The environment for the shell.
 */
void	init_mini(t_mini *mini, char **env, char *name)
{
	mini->name = name;
	mini = malloc(sizeof(t_mini));
	if (!mini)
		clean_exit(NULL);
	mini->cmd = NULL;
	mini->token = NULL;
	mini->sig.status = 0;
	mini->sig.exit = 0;
	init_env(mini, env);
	increment_shell_level(mini);
	sig_init(mini);
}

/**
 * Reinitializes the mini structure and frees memory.
 * @param {t_mini*} mini - The mini structure to reinitialize.
 * @param {char*} rl - The readline string to free.
 */
void	reinit(t_mini *mini, char *rl)
{
	free_token(mini->token);
	free_cmd(mini->cmd);
	free(rl);
	mini->sig.sigint = 0;
	mini->sig.sigquit = 0;
}
