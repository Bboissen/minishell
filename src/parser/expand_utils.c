/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:39:25 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/07 14:23:03 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Joins tokens during the parsing.
 * 
 * @param mini Pointer to the main structure of the shell.
 */
void	token_join(t_mini **mini)
{
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
 * @brief Refactors the tokens during the parsing.
 * 
 * @param mini Pointer to the main structure of the shell.
 */
int	token_refacto(t_mini **mini)
{
	t_token	*tmp_token;

	if ((*mini)->token == (*mini)->h_token && !(*mini)->token->next)
		return (free_token(&(*mini)->h_token), ERROR);
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
	return (SUCCESS);
}

/**
 * @brief Gets the error code from a string.
 * 
 * @param str The string to get the error code from.
 * @return {char *} - Returns the error code as a string.
 */
char	*get_error_code(char *str)
{
	char	*env_val;
	char	*tmp;

	env_val = ft_itoa(get_sig()->status);
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
