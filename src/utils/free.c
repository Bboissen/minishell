/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:45 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/23 11:22:59 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a dynamically allocated 2D array.
 * 
 * @param tab The 2D array to be freed.
 */
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_memdel(tab[i]);
		i++;
	}
	if (tab)
		ft_memdel(tab);
}

/**
 * @brief Frees a dynamically allocated command structure.
 * 
 * @param cmd The command structure to be freed.
 */
void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while ((*cmd))
	{
		tmp = (*cmd)->next;
		if ((*cmd)->args)
			free_tab((*cmd)->args);
		if ((*cmd)->in)
			free((*cmd)->in);
		if ((*cmd)->out)
			free((*cmd)->out);
		close_fds((*cmd)->fd);
		free((*cmd));
		(*cmd) = tmp;
	}
	(*cmd) = NULL;
}

/**
 * @brief Frees a dynamically allocated token structure.
 * 
 * @param token The token structure to be freed.
 */
void	free_token(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		tmp = (*token)->next;
		if ((*token)->str)
		{
			free((*token)->str);
			(*token)->str = NULL;
		}
		free((*token));
		(*token) = tmp;
	}
	(*token) = NULL;
}

/**
 * @brief Frees a dynamically allocated environment variable structure.
 * 
 * @param env The environment variable structure to be freed.
 */
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		ft_memdel(env->name);
		ft_memdel(env->value);
		ft_memdel(env);
		env = tmp;
	}
}

/**
 * @brief Cleans up and exits the program.
 * 
 * This function frees all dynamically allocated memory, prints an exit message, and exits the program.
 * 
 * @param mini The main program structure.
 * @param rl The readline buffer.
 * @return The exit status of the program.
 */
int	clean_exit(t_mini *mini, char *rl)
{
	int		status;
	t_sig	*sig;

	sig = get_sig();
	if (mini)
		status = sig->status;
	else
		exit(MALLOC);
	if (mini->token)
		free_token(&(mini->token));
	if (mini->cmd)
		free_cmd(&(mini->cmd));
	if (mini->env)
		free_env(mini->env);
	if (sig->exit == 1 || rl == NULL)
		ft_putstr_fd("exit\n", 2);
	free(mini);
	exit(status);
	return (status);
}
