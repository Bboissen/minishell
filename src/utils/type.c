/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:54 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/26 15:16:45 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a token is of a specific type.
 * 
 * @param token The token to check.
 * @param type The type to compare with the token's type.
 * @return int Returns TRUE if the token is of the specified type,
 * FALSE otherwise.
 */
int	is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * @brief Checks if a token is of any of the types specified in a string.
 * 
 * @param token The token to check.
 * @param types A string where each character represents a type.
 * @return int Returns TRUE if the token is of any of the
 * specified types, FALSE otherwise.
 */
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

/*not used*/
/**
 * @brief Checks if a token of a specific type exists in the token list.
 * 
 * @param token The starting point in the token list.
 * @param type The type to search for.
 * @return int Returns TRUE if a token of the specified type
 * is found, FALSE otherwise.
 */
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

/**
 * @brief Checks if a PIPE type token exists in the token
 * list before an END type token.
 * 
 * @param token The starting point in the token list.
 * @return int Returns TRUE if a PIPE type token is found
 * before an END type token, FALSE otherwise.
 */
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

/*not used*/
/**
 * @brief Finds the next token of a specific type in the token list.
 * 
 * @param token The starting point in the token list.
 * @param type The type of token to find.
 * @param skip If true, start searching from the next token in the list.
 * @return t_token* The next token of the specified type,
 * or NULL if no such token is found.
 */
t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}
