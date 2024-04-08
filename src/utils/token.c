/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:51 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/08 14:19:10 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*not used*/
/**
 * @brief Finds the next separator token in the token list.
 * 
 * @param token The starting point in the token list.
 * @return t_token* The next separator token, or NULL if no such token is found.
 */
t_token	*next_sep(t_token *token)
{
	if (token && token->skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

/*not used*/
/**
 * @brief Finds the previous separator token in the token list.
 * 
 * @param token The starting point in the token list.
 * @return t_token* The previous separator token, 
 * or NULL if no such token is found.
 */
t_token	*prev_sep(t_token *token)
{
	if (token && token->skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

/**
 * @brief Finds the next runnable token in the token list.
 * 
 * @param token The starting point in the token list.
 * @return t_token* The next runnable token, or NULL if no such token is found.
 */
t_token	*next_run(t_token *token)
{
	if (token && token->skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

/**
 * @brief Processes all tokens in the mini structure.
 * 
 * @param mini The mini structure containing the tokens to process.
 */
void	process_tokens(t_mini *mini)
{
	t_token	*token;

	token = mini->token;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
}

/**
 * @brief Updates the pointers of a token and its previous token.
 * 
 * @param token The token whose pointers are to be updated.
 * @param prev The previous token.
 */
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
