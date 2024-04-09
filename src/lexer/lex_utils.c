/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:04:00 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/09 13:32:15 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/minishell.h"

static char	*token_typer(t_mini *mini, t_type type[3], char *str);
static void	new_token(t_mini *mini, t_token **token,
				char *str, t_type options[3]);
static char *random_file();

char	*syntax_check(t_mini *mini, t_token **token, char *str, int *quote)
{
	t_type	options[3];

	while (str && *quote == 0 && *str && is_space(*str))
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
	str = token_typer(mini, options, str);
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

	while (str && *quote == 0 && *str && is_space(*str))
	{
		str++;
		if (*token && (*token)->join == JOIN)
		{
			printf("token = %s\n", (*token)->str);
			(*token)->join = 0;
		}
	}
	// printf("str = %s\n", str);
	// getchar();
	if (!str || !*str || *quote != 0 || is_spechar(*str) != 0)
		return (str);
	start = str;
	while (*str && !is_space(*str) && is_spechar(*str) == 0)
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
		*quote = (++(*quote)) % 2;
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
	if (*(str) && is_spechar(*(str)) != 2 && !is_space(*(str)))
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
		*quote = (++(*quote)) % 2;
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
	if (end == '$' || ((*(str + 1) && is_spechar(*(str + 1)) != 2 && !is_space(*(str + 1)))))
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

// """""""e""""""""""c""""""""""""h""""""""o""""""""""""""""""""" bonjour should not join
//solve by adding a while 
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
	if (*str && !is_space(*str) && !is_spe_expand(*str))
	{
		start = str;
		flag++;
	}
	while (*str && !is_space(*str) && is_spechar(*str) == 0
		&& (flag == 0 || !is_spe_expand(*str)))
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

static char	*token_typer(t_mini *mini, t_type type[3], char *str)
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
	{
		mini->sig.exit = MALLOC;
		return ;
	}
	if (str)
	{
		new_token->str = ft_strdup(str);
		if (!new_token->str)
		{
			mini->sig.exit = MALLOC;
			return ;
		}
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

int	is_space(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*out;

	len = 0;
	while (str[len])
		len++;
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
static char *random_file()
{
	char *file;
	char *tmp;
	int i;

	file = ft_strdup("/tmp/");
	i = 0;
	while (i < 10)
	{
		tmp = ft_itoa(rand() % 10);
		file = ft_strjoin_free(file, tmp, 3);
		i++;
	}
	return (file);
}

