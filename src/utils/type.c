/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:54 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/18 18:10:58 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (TRUE);
	else
		return (FALSE);
}

int	is_types(t_token *token, char *types)
{
	if ((ft_strchr(types, ' ') && is_type(token, EMPTY))
		|| (ft_strchr(types, 'X') && is_type(token, CMD))
		|| (ft_strchr(types, 'x') && is_type(token, ARG))
		|| (ft_strchr(types, 'T') && is_type(token, TRUNC))
		|| (ft_strchr(types, 'A') && is_type(token, APPEND))
		|| (ft_strchr(types, 'I') && is_type(token, INPUT))
		|| (ft_strchr(types, 'P') && is_type(token, PIPE))
		|| (ft_strchr(types, 'E') && is_type(token, END)))
		return (TRUE);
	else
		return (FALSE);
}

int	has_type(t_token *token, int type)
{
	while (token)
	{
		if (is_type(token, type))
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

int	has_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}
