/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 11:25:04 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*list_join(t_token *token);

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

	if (!ft_strcmp(str, "?"))
		return (ft_itoa(mini->sig.status));
	env_val = ft_strdup(""); //move under
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
static t_token	*list_join(t_token *token)
{
	char	*new_str;

	new_str = malloc(ft_strlen(token->str)
			+ ft_strlen(token->next->str) + 1);
	ft_strcpy(new_str, token->str);
	ft_strcat(new_str, token->next->str);
	free(token->str);
	free(token->next->str);
	token->next->str = new_str;
	token->next->prev = token->prev;
	if(token->prev)
		token->prev->next = token->next;
	free(token);
	return (token);
}
