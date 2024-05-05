/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbsn <bbsn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:39:25 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/05 23:40:26 by bbsn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	token_refacto(t_mini **mini)
{
	t_token	*tmp_token;

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
