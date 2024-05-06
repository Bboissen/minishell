/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:04:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/06 17:04:48 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initialize the mini structure with the given environment.
 * 
 * @param mini The main structure of the shell.
 * @param env The environment for the shell.
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
	(*mini)->initial_fds[0] = -1;
	(*mini)->initial_fds[1] = -1;
	init_env(mini, env);
	increment_shell_level(mini);
	sig_init();
}

/**
 * @brief Sets up and reads a line from the terminal with a custom prompt.
 * 
 * @param rl The string to store the read line.
 * @param mini The main structure of the shell.
 * @param str The string to be used as the base of the prompt.
 */
void	readline_setup(t_mini *mini, char **rl, char *str)
{
	char	*prompt;

	prompt = ft_strjoin(str, " > ");
	if (!prompt)
		error_manager(mini, MALLOC, NULL, NULL);
	*rl = readline(prompt);
	if (mini->rl == NULL && ft_strcmp(str, "heredoc"))
	{
		ft_printfd(STDERR_FILENO, "exit\n");
		free(prompt);
		clean_exit(mini);
	}
	if (*rl != NULL && ft_strcmp(*rl, "") != SUCCESS)
		add_history(*rl);
	rl_on_new_line();
	free(prompt);
}

/**
 * @brief Reinitializes the mini structure and frees memory.
 * 
 * @param mini The mini structure to reinitialize.
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

/**
 * @brief Initializes the options array.
 *
 * @param options Array of options.
 */
void	initialize_options(t_type options[3])
{
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
}
