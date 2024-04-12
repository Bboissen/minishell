/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/11 18:47:16 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expands and joins tokens in the shell.
 * @param {t_mini*} mini - The main structure of the shell.
 */
void	expand_join(t_mini *mini)
{
	char	*tmp;

	mini->token = mini->h_token;
	while (mini->token)
	{
		if (mini->token->expand)
		{
			tmp = expand_token(mini, mini->token->str);
			free(mini->token->str);
			mini->token->str = tmp;
			mini->token->expand = 0;
		}
		mini->token = mini->token->next;
	}
	mini->token = mini->h_token;
	while (mini->token)
	{
		if (mini->token->join)
			mini->token = list_join(mini->token);
		else
			mini->token = mini->token->next;
	}
}

/**
 * Expands a token in the shell.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char*} str - The string to be expanded.
 * @return {char*} - Returns the expanded string.
 */
char	*expand_token(t_mini *mini, char *str)
{
	char	*env_val;

	env_val = ft_strdup("");
	if (!ft_strcmp(str, "?"))
		return (ft_itoa(mini->sig.status));
	while (mini->env && mini->env->name)
	{
		if (!ft_strcmp(str, mini->env->name))
		{
			env_val = strdup(mini->env->value);
			return (env_val);
		}
		mini->env = mini->env->next;
	}
	return (env_val);
}

/**
 * Joins a list of tokens in the shell.
 * @param {t_token*} token - The token to be joined.
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
	if (token->type)
		token->next->type = token->type;
	if (token->skip)
		token->next->skip = token->skip;
	to_free = token;
	token = token->next;
	if (to_free->prev)
		to_free->prev->next = token;
	token->prev = to_free->prev;
	free(to_free->str);
	free(to_free);
	return (token);
}
