/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 17:39:10 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands and joins tokens in the shell.
 * @param {t_mini*} mini - The main structure of the shell.
 */
//protected random iteration
// $E"N"D"asydty"
void	expand_join(t_mini **mini)
{
	char	*tmp;

	(*mini)->token = (*mini)->h_token;
	while ((*mini)->token)
	{
		if ((*mini)->token->expand)
		{
			tmp = expand_token(mini, (*mini)->token->str); //NULL for malloc issue
			free((*mini)->token->str);
			(*mini)->token->str = tmp;
			(*mini)->token->expand = 0;
			if (!tmp[0] && (*mini)->token->join)
				(*mini)->token = list_join((*mini)->token);//now return NULL for malloc issue
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
			(*mini)->token = list_join((*mini)->token); //now return NULL for malloc issue
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
char	*expand_token(t_mini **mini, char *str)
{
	t_env *env;
	char	*env_val;
	char 	*tmp;
	t_sig	*sig;
	static int i = 0;

	sig = get_sig();
	env = (*mini)->h_env;
	env_val = NULL;
	if (!ft_strncmp(str, "?", 1))
	{
		env_val = ft_itoa(sig->status); //to protect
		if (!env_val)
			return (NULL);
		if (ft_strcmp(str, "?") != 0)
		{
			tmp = ft_strjoin(env_val, str + 1);  //to protect
			free(env_val);
			env_val = tmp;
		}
		if (!env_val)
			return (NULL);
		return (env_val);
	}
	while (env && env->name)
	{
		printf("success\n");
		if (!ft_strcmp(str, env->name))
		{
			if (i++ < 50)
				env_val = ft_strdup(env->value);  //to protect
			else
				env_val = NULL;
			if (!env_val)
				return (NULL);
			return (env_val);
		}
		env = env->next;
	}
	env_val = ft_strdup(""); //protected random iteration
	if (!env_val)
		return (NULL);
	return (env_val);
}

/**
 * Joins a list of tokens in the shell.
 * @param {t_token*} token - The token to be joined.
 * @return {t_token*} - Returns the joined token.
 */
//protected random iteration
t_token	*list_join(t_token *token)
{
	char	*new_str;
	t_token	*to_free;
	static int i = 0;

	if (i++ < 3)
		new_str = malloc(ft_strlen(token->str)
				+ ft_strlen(token->next->str) + 1);
	else
		new_str = NULL;
	if (!new_str)
		return (NULL);
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
