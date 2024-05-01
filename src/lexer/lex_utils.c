/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:04:00 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/01 17:21:01 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_typer(t_type type[3], char *str);
static void	new_token(t_mini *mini, char *str, t_type options[3]);

char	*syntax_check(t_mini *mini, char *str, int *quote)
{
	t_type	options[3];

	while (str && *quote == 0 && *str && ft_isspace(*str))
	{
		str++;
		if (mini->token && (mini->token->join == JOIN))
			mini->token->join = 0;
	}
	if (*quote != 0 || !*str || is_spechar(*str) != 2)
		return (str);
	if (((*str == '|' && (!mini->token || mini->token->type == PIPE)) || (mini->token && (mini->token->type == APPEND
					|| mini->token->type == TRUNC || mini->token->type == INPUT
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

char	*string_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	char	end;
	t_type	options[3];

	while (str && *quote == 0 && *str && ft_isspace(*str))
		str++;
	if (!str || !*str || *quote != 0 || is_spechar(*str) != 0)
		return (str);
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

char	*s_quote_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	t_type	options[3];

	if (!str || *str !='\'' || *quote != 0)
		return (str);
	while (*str == '\'')
	{
		str++;
		*quote = ((*quote) + 1) % 2;
	}
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
	if (*quote == 0 && mini->token && is_spe_builtin(mini->token->str))
		return(new_token(mini, "", options), str);
	if (*quote == 0)
		return (str);
	start = str;
	while (*str != '\'')
		str++;
	*str++ = '\0';
	if (*(str) && is_spechar(*(str)) != 2 && !ft_isspace(*(str)))
		options[1] = JOIN;
	while (*str == '\'')
		str++;
	if (*(str) && (is_spechar(*(str)) == 2 || ft_isspace(*(str))))
		options[1] = 0;
	new_token(mini, start, options);
	*quote = 0;
	return (str);
}
//echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ <<" see expansion
char	*d_quote_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	char	end;
	t_type	options[3];

	if (!str  || *str !='"' )
		return (str);
	while (*str == '"')
	{
		str++;
		*quote = ((*quote) + 1) % 2;
	}
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
	if (*quote == 0 && mini->token && is_spe_builtin(mini->token->str))
		return(new_token(mini, "", options), str);
	else if (*quote == 0)
		return (str);
	start = str;
	printf("start: %s\n", start);
	while (*str != '"' && *str != '$')
		str++;
	end = *str;
	*str = '\0';
	if (end == '$' || ((*(str + 1) && is_spechar(*(str + 1)) != 2 && !ft_isspace(*(str + 1)))))
		options[1] = JOIN;
	if (strlen(start) > 0)
		new_token(mini, start, options);
	if (end == '"')
	{
		*quote = 0;
		str++;
	}
	else
		*str = end;
	return (str);
}

char	*var_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	char	end;
	int		flag;
	t_type	options[3];

	if (!str || *str != '$')
		return (str);
	start = str++;
	flag = 0;
	if (*str && !ft_isspace(*str) && !ft_isdigit(*str) && (!is_spe_expand(*str) || *str == '?'))
	{
		start = str;
		flag++;
	}
	while (*str && !ft_isspace(*str) && is_spechar(*str) == 0
		&& (flag == 0 || !is_spe_expand(*str) || *str == '?'))
		str++;
	end = *str;
	*str = '\0';
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
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

static char	*token_typer(t_type type[3], char *str)
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

//protected random iteration
static void	new_token(t_mini *mini, char *str, t_type options[3])
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token)); //protected random iteration
	if (!new_token)
		return (lexer_err(mini, NULL, MALLOC, 0));
	if (str)
	{
		new_token->str = ft_strdup(str); //protected random iteration
		if (!new_token->str)
			return (free(new_token), lexer_err(mini, NULL, MALLOC, 0));
	}
	else
		new_token->str = NULL;
	new_token->type = options[0];
	new_token->join = options[1];
	new_token->expand = options[2];
	new_token->next = NULL;
	if (!mini->token)
	{
		new_token->prev = NULL;
		mini->token = new_token;
		mini->h_token = mini->token;
	}
	else
	{
		new_token->prev = mini->token;
		mini->token->next = new_token;
		mini->token = mini->token->next;
	}
}
