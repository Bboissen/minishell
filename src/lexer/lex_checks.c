/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:17:13 by talibabtou        #+#    #+#             */
/*   Updated: 2024/05/05 11:40:54 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	string_setter(char **str, char **start);
static void	initialize_options(t_type options[3]);

/**
 * @brief Checks the syntax of the input string.
 * If the syntax is incorrect, it returns NULL.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Input string.
 * @param quote Pointer to the quote variable.
 * @return {char *} - Returns the updated string pointer.
 */
char	*syntax_check(t_mini *mini, char *str, int *quote)
{
	t_type	options[3];

	if (*quote != 0 || !*str || is_spechar(*str) != 2)
		return (str);
	if (((*str == '|' && (!mini->token || mini->token->type == PIPE))
			|| (mini->token && (mini->token->type == APPEND
					|| mini->token->type == TRUNC
					|| mini->token->type == INPUT
					|| mini->token->type == HEREDOC))))
	{
		lexer_err(mini, NULL, PARSE, *str);
		return (NULL);
	}
	str = token_typer(options, str);
	options[1] = 0;
	options[2] = 0;
	new_token(mini, NULL, options);
	return (++str);
}

/**
 * @brief Handles the string input, processes the string
 * input and generates tokens.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Input string.
 * @param quote Pointer to the quote variable.
 * @return {char *} - Returns the updated string pointer.
 */
char	*string_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	char	end;
	t_type	options[3];

	while (str && *quote == 0 && *str && ft_isspace(*str))
		str++;
	if (!str || !*str || *quote != 0 || is_spechar(*str) != 0)
		return (str);
	if (*str == '~')
		return (home_handler(mini, str));
	start = str;
	while (*str && !ft_isspace(*str) && is_spechar(*str) == 0)
		str++;
	end = *str;
	*str = 0;
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
	if (is_spechar(end) == 1)
		options[1] = JOIN;
	new_token(mini, start, options);
	if (end)
		*str = end;
	return (str);
}

/**
 * @brief Handles the variable input, processes the
 * variable input and generates tokens.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Input string.
 * @param quote Pointer to the quote variable.
 * @return {char *} - Returns the updated string pointer.
 */
char	*var_handler(t_mini *mini, char *str, int *quote)
{
	char	end;
	t_type	options[3];
	int		flag;
	char	*start;

	if (!str || *str != '$')
		return (str);
	flag = string_setter(&str, &start);
	end = *str;
	initialize_options(options);
	if (flag == 1)
		options[2] = EXPAND;
	if ((*quote == 0 && (is_spechar(end) == 1 || is_spe_expand(end)))
		|| (*quote == 1 && *(str + 1) && is_spechar(*(str + 1)) < 2)
		|| (*quote == 1 && end != '"'))
		options[1] = JOIN;
	if (*start)
		new_token(mini, start, options);
	if (end == '"' && *quote == 1)
	{
		*quote = 0;
		str++;
	}
	else
		*str = end;
	return (str);
}

/**
 * @brief This function prepares the string for variable
 * handling by setting the start and end pointers.
 *
 * @param str Input string.
 * @return {char *} - Returns the updated string pointer.
 */
static int	string_setter(char **str, char **start)
{
	int		flag;

	*start = (*str)++;
	flag = 0;
	if (**str && !ft_isspace(**str) && !ft_isdigit(**str)
		&& (!is_spe_expand(**str) || **str == '?'))
	{
		*start = *str;
		flag++;
	}
	while (**str && !ft_isspace(**str) && is_spechar(**str) == 0
		&& (flag == 0 || !is_spe_expand(**str) || **str == '?'))
		(*str)++;
	**str = '\0';
	return (flag);
}

/**
 * @brief Initializes the options array.
 *
 * @param options Array of options.
 */
static void	initialize_options(t_type options[3])
{
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
}
