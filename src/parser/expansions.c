/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/24 12:21:46 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands and joins tokens in the shell.
 * @param {t_mini*} mini - The main structure of the shell.
 */
//protected random iteration
void	expand_join(t_mini **mini)
{
	char	*tmp;

	(*mini)->token = (*mini)->h_token;
	while ((*mini)->token)
	{
		if ((*mini)->token->expand)
		{
			tmp = expand_token(mini, (*mini)->token->str); //protected random iteration
			free((*mini)->token->str);
			(*mini)->token->str = tmp;
			(*mini)->token->expand = 0;
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
			(*mini)->token = list_join((*mini), (*mini)->token); //protected random iteration
		}
		else
			(*mini)->token = (*mini)->token->next;
	}
}

/**
 * Expands a token in the shell.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char*} str - The string to be expanded.
 * @return {char*} - Returns the expanded string.
 */
//protected random iteration
char	*expand_token(t_mini **mini, char *str)
{
	t_env *env;
	char	*env_val;
	t_sig	*sig;

	sig = get_sig();
	env = (*mini)->h_env;
	env_val = NULL;
	if (!ft_strcmp(str, "?"))
	{
		env_val = ft_itoa(sig->status); //protected random iteration
		if (!env_val)
			error_manager(*mini, MALLOC, NULL, NULL); 
		return (env_val);
	}
	while (env && env->name)
	{
		if (!ft_strcmp(str, env->name))
		{
			env_val = ft_strdup(env->value); //protected random iteration
			if (!env_val)
				error_manager(*mini, MALLOC, NULL, NULL);
			return (env_val);
		}
		env = env->next;
	}
	env_val = ft_strdup(""); //protected random iteration
	if (!env_val)
		error_manager(*mini, MALLOC, NULL, NULL);
	return (env_val);
}

/**
 * Joins a list of tokens in the shell.
 * @param {t_token*} token - The token to be joined.
 * @return {t_token*} - Returns the joined token.
 */
//protected random iteration
t_token	*list_join(t_mini *mini, t_token *token)
{
	char	*new_str;
	t_token	*to_free;

	new_str = malloc(ft_strlen(token->str)
				+ ft_strlen(token->next->str) + 1); //protected random iteration
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
