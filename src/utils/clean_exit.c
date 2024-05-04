/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:45 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 11:22:29 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all allocated memory and exits the program.
 * 
 * @param mini The main structure of the program.
 */
int	clean_exit(t_mini *mini)
{
	int		status;
	t_sig	*sig;

	sig = get_sig();
	if (mini)
		status = sig->status;
	else
		exit(MALLOC);
	mini->env = mini->h_env;
	mini->token = mini->h_token;
	mini->cmd = mini->h_cmd;
	if (mini->token)
		free_token(&(mini->token));
	if (mini->cmd)
		free_cmd(&(mini->cmd));
	if (mini->env)
		free_env(mini->env);
	if (mini->rl)
		free(mini->rl);
	rl_clear_history();
	free(mini);
	exit(status);
}

/**
 * @brief Frees a linked list of tokens.
 * 
 * @param token The head of the linked list of tokens.
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
 * @brief Frees a linked list of commands.
 * 
 * @param cmd The head of the linked list of commands.
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
 * @brief Frees a null-terminated array of strings.
 * 
 * @param tab The array of strings to free.
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
 * @brief Frees a linked list of environment variables.
 * 
 * @param env The head of the linked list of environment variables.
 */
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->name)
			ft_memdel(env->name);
		if (env->value)
			ft_memdel(env->value);
		ft_memdel(env);
		env = tmp;
	}
}
