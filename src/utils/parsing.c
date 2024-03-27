/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:48 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/26 11:08:49 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character in a line is a separator.
 * 
 * @param line The line of text to check.
 * @param i The index of the character to check.
 * @return int Returns TRUE if the character is a separator, FALSE otherwise.
 */
int	is_sep(char *line, int i)
{
	if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * @brief Checks if a separator in a line should be ignored.
 * 
 * @param line The line of text to check.
 * @param i The index of the character to check.
 * @return int Returns TRUE if the separator should be ignored, FALSE otherwise.
 */
int	ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (TRUE);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (TRUE);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (TRUE);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
		&& line[i + 2] && line[i + 2] == '>')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Checks the status of quotes at a given index in a line.
 * 
 * @param line The line of text to check.
 * @param index The index to check.
 * @return int Returns the status of quotes at the given index.
 */
int	quotes(char *line, int index)
{
	int	i;
	int	quote_open;

	i = 0;
	quote_open = 0;
	while (line[i] && i <= index)
	{
		if (i > 0 && line[i - 1] == '\\')
			continue ;
		else if (quote_open == 0 && line[i] == '\"')
			quote_open = 1;
		else if (quote_open == 0 && line[i] == '\'')
			quote_open = 2;
		else if (quote_open == 1 && line[i] == '\"')
			quote_open = 0;
		else if (quote_open == 2 && line[i] == '\'')
			quote_open = 0;
		i++;
	}
	return (quote_open);
}

/**
 * @brief Checks if a token is the last valid argument.
 * 
 * @param token The token to check.
 * @return int Returns TRUE if the token is the last valid argument, FALSE otherwise.
 */
int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
			return (1);
	}
	return (0);
}

/**
 * @brief Checks a line of tokens for syntax errors.
 * 
 * @param mini The mini structure containing the tokens to check.
 * @param token The starting point in the token list.
 * @return int Returns TRUE if no syntax errors are found, FALSE otherwise.
 */
int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI")
			&& (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			if (token->next)
				ft_putstr_fd(token->next->str, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			return (mini->sig.status = 258, FALSE);
		}
		if (is_types(token, "PE")
			&& (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			return (mini->sig.status = 258, FALSE);
		}
		token = token->next;
	}
	return (TRUE);
}
