/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:33:41 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/07 13:16:05 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_all_tests(t_mini *mini, char *str, int *quote);
// static void	insert_new_token(t_mini *mini, t_token *new_token);

/**
 * @brief Main lexer function, processes the input
 * string and generates tokens.
 *
 * @param mini Pointer to the t_mini structure.
 */
void	lexer(t_mini *mini)
{
	int		quote;
	char	*str;

	str = mini->rl;
	if (odd_quote(str))
		return (lexer_err(mini, NULL, QUOTE, 0));
	mini->token = NULL;
	quote = 0;
	while (str && *str != 0)
	{
		while (str && quote == 0 && *str && ft_isspace(*str))
		{
			str++;
			if (mini->token && (mini->token->join == JOIN))
				mini->token->join = 0;
		}
		str = handle_all_tests(mini, str, &quote);
	}
	if (mini->token && mini->token->type != STR)
		return (lexer_err(mini, NULL, PARSE, 0));
	if (mini->token && mini->token->join == JOIN)
		mini->token->join = 0;
	mini->token = mini->h_token;
}

/**
 * @brief Handles all tests.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Input string.
 * @param quote Pointer to the quote variable.
 */
static char	*handle_all_tests(t_mini *mini, char *str, int *quote)
{
	str = syntax_check(mini, str, quote);
	str = string_handler(mini, str, quote);
	str = s_quote_handler(mini, str, quote);
	str = d_quote_handler(mini, str, quote);
	str = var_handler(mini, str, quote);
	return (str);
}

/**
 * @brief Creates a new token.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Input string.
 * @param options Array of token options.
 */
void	new_token(t_mini *mini, char *str, t_type options[3])
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (lexer_err(mini, NULL, MALLOC, 0));
	if (str)
	{
		new_token->str = ft_strdup(str);
		if (!new_token->str)
			return (ft_memdel(new_token), lexer_err(mini, NULL, MALLOC, 0));
	}
	else
		new_token->str = NULL;
	new_token->type = options[0];
	new_token->join = options[1];
	new_token->expand = options[2];
	new_token->next = NULL;
	insert_new_token(mini, new_token);
}

/**
 * @brief Inserts a new token into the token list.
 *
 * @param mini Pointer to the t_mini structure.
 * @param new_token Pointer to the new token.
 */
void	insert_new_token(t_mini *mini, t_token *new_token)
{
	if (!mini->token)
	{
		new_token->prev = NULL;
		mini->token = new_token;
		mini->h_token = mini->token;
	}
	else
	{
		if (mini->token->next)
		{
			printf("new %s\n", mini->token->str);
			new_token->next = mini->token->next;
			mini->token->next->prev = new_token;
			mini->token->next = new_token;
		}
		new_token->prev = mini->token;
		mini->token->next = new_token;
		mini->token = mini->token->next;
	}
}

/**
 * @brief Determines the type of the token.
 *
 * @param type Array of token types.
 * @param str Input string.
 * @return {char *} - Returns the updated string pointer.
 */
char	*token_typer(t_type type[3], char *str)
{
	if (!str || *str == '|')
		type[0] = PIPE;
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
		{
			type[0] = APPEND;
			str++;
		}
		else
			type[0] = TRUNC;
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			type[0] = HEREDOC;
			str++;
		}
		else
			type[0] = INPUT;
	}
	return (str);
}
