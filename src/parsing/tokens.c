/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:35 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/26 10:54:09 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Defines the type of the token
 * 
 * @param token Pointer to the token whose type is to be defined
 * @param separator Integer representing whether a separator is present or not
 */
void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == SUCCESS)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == SUCCESS && !separator)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == SUCCESS && !separator)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == SUCCESS && !separator)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == SUCCESS && !separator)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == SUCCESS && !separator)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

/**
 * @brief Squishes arguments in the mini structure
 * 
 * @param mini Pointer to the mini structure
 */
void	squish_args(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->token;
	while (token)
	{
		prev = prev_sep(token);
		if (is_type(token, ARG) && is_types(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			update_token_pointers(token, prev);
			update_mini_start(mini, token);
		}
		token = token->next;
	}
}

/**
 * @brief Allocates memory for the next token
 * 
 * @param line The line from which to extract the token
 * @param i Pointer to the index in the line
 * @return int The size of the memory to be allocated
 */
int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
		count = handle_quotes(line, i, &j, &c);
	return (j - count + 1);
}

/**
 * @brief Generates the next token from the line
 * 
 * @param line The line from which to extract the token
 * @param i Pointer to the index in the line
 * @return t_token* Pointer to the generated token
 */
t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	token->str = malloc(sizeof(char) * next_alloc(line, i));
	if (!token || !token->str)
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || c != ' '))
		handle_quotes(line, i, &j, &c);
	token->str[j] = '\0';
	return (token);
}

/**
 * @brief Extracts all tokens from the line
 * 
 * @param line The line from which to extract the tokens
 * @return t_token* Pointer to the first token in the linked list of tokens
 */
t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
