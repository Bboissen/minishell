/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:33:41 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/24 07:12:56 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	odd_quote(char *str);

//protected random iteration
void	lexer(t_mini *mini)
{
	int		quote;
	char	*str;

	str = mini->rl;
	if (odd_quote(str))
		return (lexer_err(mini, &str, QUOTE, 0));
	mini->token = NULL;
	quote = 0;
	while (str && *str != 0)
	{
		while (quote == 0 && *str && ft_isspace(*str))
			str++;
		str = syntax_check(mini, str, &quote);
		str = string_handler(mini, str, &quote);
		str = s_quote_handler(mini, str, &quote);
		str = d_quote_handler(mini, str, &quote);
		str = var_handler(mini, str, &quote);
	}
	if (mini->token && mini->token->type != STR)
		return (lexer_err(mini, &str, PARSE, 0));
	if (mini->token && mini->token->join == JOIN)
		mini->token->join = 0;
	mini->token = mini->h_token;
}

static int	odd_quote(char *str)
{
	int		i;
	int		s_quote;
	int		d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\'' && d_quote != 1)
				s_quote = (s_quote + 1) % 2;
			else if (str[i] == '"' && s_quote != 1)
				d_quote = (d_quote + 1) % 2;
			i++;
		}
	}
	return (s_quote % 2 || d_quote % 2);
}

int	is_spechar(char c)
{
	if (c == '\'' || c == '"' || c == '$')
		return (1);
	else if (c == '|' || c == '>' || c == '<')
		return (2);
	return (0);
}

int	is_spe_expand(char c)
{
	if ((c >= '!' && c <= '/') || (c >= ':' && c <= '@')
		|| (c >= '[' && c <= ']') || (c >= '{' && c <= '}'))
		return (1);
	else
		return (0);
}


