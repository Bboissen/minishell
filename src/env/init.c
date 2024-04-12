/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:04:59 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/11 18:38:05 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
