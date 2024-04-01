/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:04:00 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/01 12:45:57 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*token_typer(t_mini *mini, t_token *token, char *str);
static void	new_token(t_mini *mini, t_token *token, char *str, t_type options);

char	*syntax_check(t_mini *mini, t_token *token, char *str)
{
	while (*str && is_space(*str))
		str++;
	if ((*str == '|' && token->prev == NULL) || token->prev == APPEND
		|| token->prev == TRUNC || token->prev == PIPE
		|| token->prev == HEREDOC)
	{
			mini->sig.exit = lexer_err(PARSE, *str);
			return (NULL);
	}
	else if (!*str || is_spechar(*str) != 1)
		return (str);
	str = token_typer(mini, token, str);
	token->next = malloc(sizeof(t_token));
	if (!token->next)
	{
		mini->sig.exit = MALLOC;
		return (NULL);
	}
	token->next->prev = token;
	token = token->next;
	return (str);
}


char	*string_handler(t_mini *mini, t_token *token, char *str)
{
	char	*start;
	char	end;
	
	if (*str == '\'' || *str == '"' || *str == '$')
		return(str);
	start = str;
	while (*str && !is_space(*str) && is_spechar(*str) == 0)
		str++;
	end = *str;
	*str = '\0';
	if (is_spechar(end) == 2)
		new_token(mini, token, start, JOIN);
	else
		new_token(mini, token, start, 0);
	*str = end;
	return (str);
}

char	*s_quote_handler(t_mini *mini, t_token *token, char *str)
{
	
}

char	*d_quote_handler(t_mini *mini, t_token *token, char *str)
{
	
}

char	*var_handler(t_mini *mini, t_token *token, char *str)
{
	
}

static char	*token_typer(t_mini *mini, t_token *token, char *str)
{
	if (*str == '|')
		token->type = PIPE;
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
		{
			token->type = APPEND;
			str++;
		}
		else
			token->type = TRUNC;
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			token->type = HEREDOC;
			str++;
		}
		else
			token->type = INPUT;
	}
	else
		token->type = STR;
	return (str);
}

static void	new_token(t_mini *mini, t_token *token, char *str, t_type options)
{
	token->next = malloc(sizeof(t_token));
	if (!token->next)
	{
		mini->sig.exit = MALLOC;
		return (NULL);
	}
	token->next->prev = token;
	token = token->next;
	token->next = NULL;
}