/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 14:49:03 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_tokens(t_mini **mini, char *tmp);

/**
 * @brief Expands and joins tokens in the shell.
 * 
 * @param mini The main structure of the shell.
 */
void	expand_join(t_mini **mini)
{
	char	*tmp;

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
			else
				if (split_tokens(mini, tmp))
					return ;
		}
		(*mini)->token = (*mini)->token->next;
	}
	token_join(mini);
}

/**
 * @brief insert and refacto the token list.
 * 
 * @param mini The main structure of the shell.
 * @param tmp Temporary variable from the environment.
 */
static int	split_tokens(t_mini **mini, char *tmp)
{
	char	**split;
	int		i;
	t_type	options[3];

	if (ft_strchr((*mini)->token->str, ' '))
	{
		split = ft_split((*mini)->token->str, ' ');
		if (!split)
			error_manager((*mini), MALLOC, NULL, NULL);
		free((*mini)->token->str);
		(*mini)->token->str = ft_strdup(split[0]);
		if (!(*mini)->token->str)
			return (free_tab(split),
				error_manager((*mini), MALLOC, NULL, NULL), ERROR);
		i = 0;
		while (split[++i])
		{
			initialize_options(options);
			new_token((*mini), split[i], options);
		}
		free_tab(split);
	}
	else if (!tmp[0])
		return (token_refacto(mini));
	return (SUCCESS);
}

/**
 * @brief Expands a env variable.
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
 * @brief Joins a list of tokens in the shell.
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

/**
 * @brief This function fills a command with arguments.
 * 
 * @param mini The main structure of the shell.
 * @param cmd The command to be filled.
 * @param args The arguments to be added to the command.
 */
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
