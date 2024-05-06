/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:04:00 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/06 16:43:57 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the home directory token.
 *
 * @param mini Pointer to the t_mini structure.
 * @param str Input string.
 * @return {char *} - Returns the updated string pointer.
 */
char	*home_handler(t_mini *mini, char *str)
{
	t_type	options[3];

	options[0] = STR;
	options[1] = 0;
	options[2] = EXPAND;
	str++;
	if (*str && ((is_spechar(*str) == 1 || is_spe_expand(*str))))
		options[1] = JOIN;
	new_token(mini, "HOME", options);
	return (str);
}

/**
 * @brief Checks if the character is a special character.
 *
 * @param c Input character.
 * @return {int } - Returns 1 if the character is a special character,
 * 2 if it's a pipe, redirect, or heredoc symbol, otherwise returns 0.
 */
int	is_spechar(char c)
{
	if (c == '\'' || c == '"' || c == '$')
		return (1);
	else if (c == '|' || c == '>' || c == '<')
		return (2);
	return (FALSE);
}

/**
 * @brief Checks if the character is a special expand character.
 *
 * @param c Input character.
 * @return {int} - Returns 1 if the character is a special 
 * expand character, otherwise returns 0.
 */
int	is_spe_expand(char c)
{
	if ((c >= '!' && c <= '/') || (c >= ':' && c <= '@')
		|| (c >= '[' && c <= ']') || (c >= '{' && c <= '}'))
		return (1);
	else
		return (0);
}

/**
 * @brief Checks if the token is a special built-in command.
 *
 * @param token Pointer to the token.
 * @return {int } - Returns TRUE if the token is a special 
 * built-in command, otherwise returns FALSE.
 */
int	is_spe_builtin(t_token *token)
{
	char	*str;

	while (token && token->type != PIPE)
	{
		str = token->str;
		if (ft_strcmp(str, "export") == 0 || ft_strcmp(str, "exit") == 0
			|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "cd") == 0
			|| ft_strcmp(str, "ls") == 0 || ft_strcmp(str, "echo") == 0)
			return (TRUE);
		token = token->prev;
	}
	return (FALSE);
}

/**
 * @brief Determines if a join operation is needed based on
 * the quote status and character values.
 *
 * @param quote Pointer to the quote status. 0 indicates no quote,
 * 1 indicates a quote is open.
 * @param str Pointer to the current position in the string.
 * @param end Current character in the string.
 * @return {int} - JOIN if a join operation is needed, 0 otherwise.
 */
t_type	is_join(int *quote, char *str, char end)
{
	int	option;

	option = 0;
	if ((*quote == 0 && (is_spechar(end) == 1 || is_spe_expand(end)))
		|| (*quote == 1 && *(str + 1) && is_spechar(*(str + 1)) < 2)
		|| (*quote == 1 && end != '"'))
		option = JOIN;
	return (option);
}
