/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:04:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 16:25:28 by bboissen         ###   ########.fr       */
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
//protected random iteration
void	readline_setup(t_mini *mini, char **rl, char *str)
{
	char	*prompt;

	prompt = ft_strjoin(str, " > "); //protected random iteration
	if (!prompt)
		error_manager(mini, MALLOC, NULL, NULL);
	*rl = readline(prompt);
	if (mini->rl == NULL && ft_strcmp(str, "heredoc"))
	{
		ft_printfd(STDERR_FILENO, "exit\n");
		free(prompt);
		clean_exit(mini);
	}
	if (*rl != NULL && ft_strcmp(*rl, "") != SUCCESS && ft_strcmp(str, "heredoc"))
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
	if (!(*mini))
	{
		ft_printfd(STDERR_FILENO, "%s: memory allocation failed\n",
			ft_strrchr(name, '/') + 1);
		error_manager(NULL, MALLOC, NULL, NULL);
	}
	(*mini)->name = ft_strrchr(name, '/') + 1;
	(*mini)->rl = NULL;
	(*mini)->cmd = NULL;
	(*mini)->h_cmd = NULL;
	(*mini)->token = NULL;
	(*mini)->h_token = NULL;
	(*mini)->env = NULL;
	(*mini)->h_env = NULL;
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
void	reinit(t_mini **mini)
{
	(*mini)->token = (*mini)->h_token;
	(*mini)->cmd = (*mini)->h_cmd;
	if ((*mini)->token)
	{
		free_token(&((*mini)->token));
		(*mini)->token = NULL;
		(*mini)->h_token = NULL;
	}
	(*mini)->cmd = (*mini)->h_cmd;
	if ((*mini)->cmd)
	{
		free_cmd(&((*mini)->cmd));
		(*mini)->cmd = NULL;
		(*mini)->h_cmd = NULL;
	}
	if ((*mini)->rl)
	{
		free((*mini)->rl);
		(*mini)->rl = NULL;
	}
	delete_heredoc((*mini));
}

t_sig	*get_sig(void)
{
	static t_sig	sig;

	return (&sig);
}
