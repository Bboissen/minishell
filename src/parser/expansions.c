/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/05 10:54:39 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands and joins tokens in the shell.
 * 
 * @param mini The main structure of the shell.
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
			if (!tmp)
				error_manager((*mini), MALLOC, NULL, NULL);
			free((*mini)->token->str);
			(*mini)->token->str = tmp;
			(*mini)->token->expand = 0;
			if (!tmp[0] && (*mini)->token->join)
			{
				(*mini)->token = list_join((*mini)->token);
				if (!(*mini)->token)
					error_manager((*mini), MALLOC, NULL, NULL);
			}
			else if (!tmp[0])
				token_refacto(mini);
		}
		(*mini)->token = (*mini)->token->next;
	}
	token_join(mini);
}

/**
 * Expands a env variable.
 * 
 * @param mini The main structure of the shell.
 * @param str The string to be expanded.
 * @return {char*} - Returns the expanded string.
 */
char	*expand_token(t_mini **mini, char *str)
{
	t_env	*env;
	char	*env_val;

	env = (*mini)->h_env;
	env_val = NULL;
	if (!ft_strncmp(str, "?", 1))
		return (get_error_code(str));
	while (env && env->name)
	{
		if (!ft_strcmp(str, env->name))
		{
			env_val = ft_strdup(env->value);
			if (!env_val)
				return (NULL);
			return (env_val);
		}
		env = env->next;
	}
	env_val = ft_strdup("");
	if (!env_val)
		return (NULL);
	return (env_val);
}

/**
 * Joins a list of tokens in the shell.
 * 
 * @param token The token to be joined.
 * @return {t_token*} - Returns the joined token.
 */
t_token	*list_join(t_token *token)
{
	char	*new_str;
	t_token	*to_free;

	new_str = malloc(ft_strlen(token->str)
			+ ft_strlen(token->next->str) + 1);
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

void	cmd_filler(t_mini *mini, t_cmd **cmd, char *args)
{
	(*cmd)->args = malloc(sizeof(char *) * 2);
	if ((*cmd)->args == NULL)
	{
		free_cmd(cmd);
		free(args);
		error_manager(mini, MALLOC, NULL, NULL);
	}
	(*cmd)->args[0] = args;
	(*cmd)->args[1] = NULL;
}
