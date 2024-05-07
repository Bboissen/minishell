/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:24:11 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 09:40:59 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_squotes(char *str, int **quote);
static char	*process_dquotes(char *str, int **quote);
static void	update_quote_and_str(char end, int *quote, char **str);

/**
 * @brief Handles single quote characters in the input string.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Pointer to the input string.
 * @param quote Pointer to the quote status.
 * @return {char *} - Returns the updated string pointer.
 */
char	*s_quote_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	t_type	options[3];

	if (!str || *str != '\'' || *quote != 0)
		return (str);
	str = process_squotes(str, &quote);
	initialize_options(options);
	if (*quote == 0 && mini->token
		&& !mini->token->join && is_spe_builtin(mini->token))
		return (new_token(mini, "\0", options), str);
	if (*quote == 0)
		return (str);
	start = str;
	while (*str && *str != '\'')
		str++;
	*str++ = '\0';
	if (*(str) && is_spechar(*(str)) != 2 && !ft_isspace(*(str)))
		options[1] = JOIN;
	if (*(str) && (is_spechar(*(str)) == 2 || ft_isspace(*(str))))
		options[1] = 0;
	new_token(mini, start, options);
	while (*str && *str == '\'')
		str++;
	*quote = 0;
	return (str);
}

/**
 * @brief Processes single quote characters in the input string.
 *
 * @param str Pointer to the input string.
 * @param quote Double pointer to the quote status.
 * @return {char *}Returns the updated string pointer.
 */
static char	*process_squotes(char *str, int **quote)
{
	while (*str == '\'')
	{
		str++;
		**quote = ((**quote) + 1) % 2;
	}
	return (str);
}

/**
 * @brief Handles double quote characters in the input string.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Pointer to the input string.
 * @param quote Pointer to the quote status.
 * @return {char *} - Returns the updated string pointer.
 */
char	*d_quote_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	char	end;
	t_type	options[3];

	if (*quote == 0 && (!str || *str != '"' ))
		return (str);
	str = process_dquotes(str, &quote);
	initialize_options(options);
	if (*quote == 0 && *str && mini->token
		&& !mini->token->join && is_spe_builtin(mini->token))
		return (new_token(mini, "\0", options), str);
	else if (*quote == 0)
		return (str);
	start = str;
	while (*str != '"' && *str != '$')
		str++;
	end = *str;
	*str = '\0';
	if (end == '$' || ((*(str + 1) && is_spechar(*(str + 1)) != 2
				&& !ft_isspace(*(str + 1)))))
		options[1] = JOIN;
	if (strlen(start) > 0)
		new_token(mini, start, options);
	update_quote_and_str(end, quote, &str);
	return (str);
}

/**
 * @brief Processes double quote characters in the input string.
 *
 * @param str Pointer to the input string.
 * @param quote Double pointer to the quote status.
 * @return {char *} - Returns the updated string pointer.
 */
static char	*process_dquotes(char *str, int **quote)
{
	while (*str == '"')
	{
		str++;
		**quote = ((**quote) + 1) % 2;
	}
	return (str);
}

/**
 * @brief Updates the quote status and the string pointer
 * based on the end character.
 *
 * @param end The end character.
 * @param quote Pointer to the quote status.
 * @param str Double pointer to the string.
 */
static void	update_quote_and_str(char end, int *quote, char **str)
{
	if (end == '"')
	{
		*quote = 0;
		(*str)++;
	}
	else
		**str = end;
}
