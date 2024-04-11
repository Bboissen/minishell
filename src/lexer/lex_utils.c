/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:04:00 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/11 18:31:01 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_typer(t_type type[3], char *str);
static void	new_token(t_mini *mini, t_token **token,
				char *str, t_type options[3]);

char	*syntax_check(t_mini *mini, t_token **token, char *str, int *quote)
{
	t_type	options[3];

	while (str && *quote == 0 && *str && ft_isspace(*str))
	{
		str++;
		if (*token && (*token)->join == JOIN)
			(*token)->join = 0;
	}
	if (*quote != 0 || !*str || is_spechar(*str) != 2)
		return (str);
	if (((*str == '|' && !(*token))
			|| ((*token) && ((*token)->type == APPEND || (*token)->type == TRUNC
					|| (*token)->type == INPUT || (*token)->type == HEREDOC
					|| (*token)->type == PIPE))))
	{
		mini->sig.exit = lexer_err(PARSE, *str);
		return (NULL);
	}
	str = token_typer(options, str);
	options[1] = 0;
	options[2] = 0;
	new_token(mini, token, NULL, options);
	return (++str);
}

char	*string_handler(t_mini *mini, t_token **token, char *str, int *quote)
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
	new_token(mini, token, start, options);
	if (end)
		*str = end;
	return (str);
}

char	*s_quote_handler(t_mini *mini, t_token **token, char *str, int *quote)
{
	char	*start;
	t_type	options[3];

	if (!str || *quote != 0)
		return (str);
	while (*str == '\'')
	{
		str++;
		*quote = ((*quote) + 1) % 2;
	}
	if (*quote == 0)
		return (str);
	start = str;
	while (*str != '\'')
		str++;
	*str++ = '\0';
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
	if (*(str) && is_spechar(*(str)) != 2 && !ft_isspace(*(str)))
		options[1] = JOIN;
	new_token(mini, token, start, options);
	*quote = 0;
	return (str);
}

char	*d_quote_handler(t_mini *mini, t_token **token, char *str, int *quote)
{
	char	*start;
	char	end;
	t_type	options[3];

	if (!str)
		return (str);
	while (*str == '"')
	{
		str++;
		*quote = ((*quote) + 1) % 2;
	}
	if (*quote == 0)
		return (str);
	start = str;
	while (*str != '"' && *str != '$')
		str++;
	end = *str;
	*str = '\0';
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
	if (end == '$' || ((*(str + 1) && is_spechar(*(str + 1)) != 2 && !ft_isspace(*(str + 1)))))
		options[1] = JOIN;
	if (strlen(start) > 0)
		new_token(mini, token, start, options);
	if (end == '"')
	{
		*quote = 0;
		str++;
	}
	else
		*str = end;
	return (str);
}

char	*var_handler(t_mini *mini, t_token **token, char *str, int *quote)
{
	char	*start;
	char	end;
	int		flag;
	t_type	options[3];

	if (!str || *str != '$')
		return (str);
	start = str++;
	flag = 0;
	printf("str = %s\n", str);
	if (*str && !ft_isspace(*str) && (!is_spe_expand(*str) || *str == '?'))
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
		new_token(mini, token, start, options);
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

static void	new_token(t_mini *mini, t_token **token,
	char *str, t_type options[3])
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		mini->sig.exit = MALLOC;
	if (str && (mini->sig.exit != MALLOC))
	{
		new_token->str = ft_strdup(str);
		if (!new_token->str)
			mini->sig.exit = MALLOC;
	}
	else
		new_token->str = NULL;
	if (mini->sig.exit == MALLOC)
		return ;
	new_token->type = options[0];
	new_token->join = options[1];
	new_token->expand = options[2];
	new_token->next = NULL;
	if (!mini->token)
	{
		new_token->prev = NULL;
		*token = new_token;
		mini->token = *token;
	}
	else
	{
		new_token->prev = *token;
		(*token)->next = new_token;
		*token = (*token)->next;
	}
	return ;
}

