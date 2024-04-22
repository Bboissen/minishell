/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:04:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/22 14:43:51 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets up and reads a line from the terminal with a custom prompt.
 * 
 * @param {char*} rl - The string to store the read line.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char*} str - The string to be used as the base of the prompt.
 */
void	readline_setup(char **rl, char *str)
{
	char	*prompt;

	prompt = ft_strjoin(str, " > ");
	if (!prompt)
		exit(MALLOC);
	*rl = readline(prompt);
	add_history(*rl);
	rl_on_new_line();
	free(prompt);
}

/**
 * Initialize the mini structure with the given environment.
 * 
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char**} env - The environment for the shell.
 */
void	init_mini(t_mini **mini, char **env, char *name)
{
	(*mini) = malloc(sizeof(t_mini));
	(*mini)->name = name + 2;
	if (!mini)
		clean_exit(NULL);
	(*mini)->cmd = NULL;
	(*mini)->token = NULL;
	init_env(mini, env);
	increment_shell_level(mini);
	sig_init();
}

/**
 * Reinitializes the mini structure and frees memory.
 * 
 * @param {t_mini*} mini - The mini structure to reinitialize.
 * @param {char*} rl - The readline string to free.
 */
void	reinit(t_mini **mini, char **rl)
{
	(*mini)->token = (*mini)->h_token;
	(*mini)->cmd = (*mini)->h_cmd;
	if ((*mini)->token)
	{
		free_token(&((*mini)->token));
		(*mini)->token = NULL;
		(*mini)->h_token = NULL;
	}
	if ((*mini)->cmd)
	{
		(*mini)->cmd = (*mini)->h_cmd;
		free_cmd(&((*mini)->cmd));
		(*mini)->cmd = NULL;
		(*mini)->h_cmd = NULL;
	}
	free(*rl);
	delete_heredoc((*mini));
}

t_sig	*get_sig(void)
{
	static t_sig	sig;

	return (&sig);
}
