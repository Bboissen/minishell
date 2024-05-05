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
	t_token	*tmp_token;

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
			{
				if ((*mini)->token == (*mini)->h_token && !(*mini)->token->next)
					free_token(&(*mini)->h_token);
				else
				{
					tmp_token = (*mini)->token;
					if ((*mini)->token->prev)
					{
						(*mini)->token->prev->next = (*mini)->token->next;
						(*mini)->token = (*mini)->token->prev;
					}
					else
					{
						(*mini)->h_token = (*mini)->token->next;
						(*mini)->token = (*mini)->h_token;
					}
					if ((*mini)->token->next)
						(*mini)->token->next->prev = (*mini)->token->prev;
					free(tmp_token->str);
					free(tmp_token);
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
			(*mini)->token = list_join((*mini)->token);
			if (!(*mini)->token)
				error_manager((*mini), MALLOC, NULL, NULL);
		}
		else
			(*mini)->token = (*mini)->token->next;
	}
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
	char	*tmp;
	t_sig	*sig;

	sig = get_sig();
	env = (*mini)->h_env;
	env_val = NULL;
	if (!ft_strncmp(str, "?", 1))
	{
		env_val = ft_itoa(sig->status);
		if (!env_val)
			return (NULL);
		if (ft_strcmp(str, "?") != 0)
		{
			tmp = ft_strjoin(env_val, str + 1);
			free(env_val);
			env_val = tmp;
		}
		if (!env_val)
			return (NULL);
		return (env_val);
	}
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
int	path_finder(t_mini *mini, t_cmd **cmd, char *str)
{
	t_env	*local_env;
	int		err;
	char	*args;
	char	**path;

	args = NULL;
	local_env = mini->h_env;
	while (local_env && ft_strcmp(local_env->name, "PATH"))
		local_env = local_env->next;
	if (!local_env)
		return (0);
	path = ft_split(local_env->value, ':');
	if (path)
	{
		args = path_checker(str, args, path, &err);
		free_tab(path);
	}
	if (path == NULL || (args == NULL && err == 0))
		return (free_cmd(cmd), error_manager(mini, MALLOC, NULL, NULL));
	else if (err == -1)
		return (err);
	else
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
	return (0);
}