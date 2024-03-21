/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:46:29 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/18 17:59:49 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_token_pointers(t_token *token, t_token *prev)
{
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = prev;
	if (token->next == (prev))
		token->next = prev->next;
	else
		token->next = NULL;
	if (prev)
	{
		prev->next->prev = token;
		prev->next = token;
	}
}

void	update_mini_start(t_mini *mini, t_token *token)
{
	if (mini->start->prev)
		mini->start = mini->start->prev;
	else
		mini->start = token;
}

int	handle_quotes(char *line, int *i, int *j, char *c)
{
	int	count;

	count = 0;
	if (*c == ' ' && (line[*i + *j] == '\'' || line[*i + *j] == '\"'))
		*c = line[*i + (*j)++];
	else if (*c != ' ' && line[*i + *j] == *c)
	{
		count += 2;
		*c = ' ';
		(*j)++;
	}
	else
		(*j)++;
	return (count);
}

