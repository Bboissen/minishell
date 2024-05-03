/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 15:03:30 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands and joins tokens in the shell.
 * @param {t_mini*} mini - The main structure of the shell.
 */
void	expand_join(t_mini **mini)
{
	char	*tmp;

	(*mini)->token = (*mini)->h_token;
	while ((*mini)->token)
	{
		if ((*mini)->token->expand)
		{
			tmp = expand_token(mini, (*mini)->token->str);
			free((*mini)->token->str);
			(*mini)->token->str = tmp;
			(*mini)->token->expand = 0;
			if (!tmp[0] && (*mini)->token->join)
				(*mini)->token = list_join((*mini), (*mini)->token);
			else if (!tmp[0])
			{
				if ((*mini)->token == (*mini)->h_token && !(*mini)->token->next)
					free_token(&(*mini)->h_token);
				else
				{
					if ((*mini)->token->prev)
						(*mini)->token->prev->next = (*mini)->token->next;
					else
						(*mini)->h_token = (*mini)->token->next;
					if ((*mini)->token->next)
						(*mini)->token->next->prev = (*mini)->token->prev;
					free((*mini)->token->str);
					free((*mini)->token);
				}
			}
		}
		(*mini)->token = (*mini)->token->next;
	}
	(*mini)->token = (*mini)->h_token;
	while ((*mini)->token)
	{
		if ((*mini)->token->join)
		{
			if ((*mini)->token == (*mini)->h_token)
				(*mini)->h_token = (*mini)->token->next;
			(*mini)->token = list_join((*mini), (*mini)->token);
		}
		else
			(*mini)->token = (*mini)->token->next;
	}
}

/**
 * Expands a token in the shell.
 * 
 * @param mini - The main structure of the shell.
 * @param str - The string to be expanded.
 * @return {char*} - Returns the expanded string.
 */
char	*expand_token(t_mini **mini, char *str)
{
	t_env	*env;
	char	*env_val;
	char	*tmp;
	t_sig	*sig;

	sig = get_sig();
	env = (*mini)->h_env;
	env_val = NULL;
	if (!ft_strncmp(str, "?", 1))
	{
		env_val = ft_itoa(sig->status);
		if (!env_val)
			error_manager(*mini, MALLOC, NULL, NULL);
		if (ft_strcmp(str, "?") != 0)
		{
			tmp = ft_strjoin(env_val, str + 1);
			free(env_val);
			env_val = tmp;
		}
		if (!env_val)
			error_manager(*mini, MALLOC, NULL, NULL);
		return (env_val);
	}
	while (env && env->name)
	{
		if (!ft_strcmp(str, env->name))
		{
			env_val = ft_strdup(env->value);
			if (!env_val)
				error_manager(*mini, MALLOC, NULL, NULL);
			return (env_val);
		}
		env = env->next;
	}
	env_val = ft_strdup("");
	if (!env_val)
		error_manager(*mini, MALLOC, NULL, NULL);
	return (env_val);
}

/**
 * Joins a list of tokens in the shell.
 * 
 * @param token - The token to be joined.
 * @return {t_token*} - Returns the joined token.
 */

t_token	*list_join(t_mini *mini, t_token *token)
{
	char	*new_str;
	t_token	*to_free;

	new_str = malloc(ft_strlen(token->str)
			+ ft_strlen(token->next->str) + 1);
	if (!new_str)
		error_manager(mini, MALLOC, NULL, NULL);
	ft_strcpy(new_str, token->str);
	ft_strcat(new_str, token->next->str);
	free(token->next->str);
	token->next->str = new_str;
	to_free = token;
	token = token->next;
	if (to_free->prev)
		to_free->prev->next = token;
	token->prev = to_free->prev;
	free(to_free->str);
	free(to_free);
	return (token);
}
