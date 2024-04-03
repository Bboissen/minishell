/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:33:41 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/03 17:18:13 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*<infile1 grep a >outfile1 | <infile1 cat >outfile2 | <infile2 sed "s/And/But/" | grep But | cat >outfile3 | cat*/

// syntax error if sequential spe charact (except $), empty string or spaces, 

// < >in"f"il'e2' grep t

int	odd_quote(char *str)
{
	int		i;
	int		s_quote;
	int		d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_quote++;
		else if (str[i] == '"')
			d_quote++;
		i++;
	}
	return (s_quote % 2 || d_quote % 2);
}

int	is_spechar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else if (c == '\'' || c == '"' || c == '$')
		return (2);
	return (0);
}

int	lexer(t_mini *mini, char *str)
{
	int		quote;
	t_token	*token;

	mini->sig.status = odd_quote(str);
	if (mini->sig.status)
		return (lexer_err(QUOTE, 0));
	token = NULL;
	mini->token = token;
	quote = 0;
	while (str && *str && mini->sig.exit == 0)
	{
		while (*str && is_space(*str))
			str++;
		str = syntax_check(mini, &token, str, &quote);
		// dprintf(2, "syntax |%s|", str);
		// getchar();
		str = string_handler(mini, &token, str, &quote);
		// dprintf(2, "string");
		// getchar();
		str = s_quote_handler(mini, &token, str, &quote);
		// dprintf(2, "s_quote");
		// getchar();
		str = d_quote_handler(mini, &token, str, &quote);
		// dprintf(2, "d_quote");
		// getchar();
		str = var_handler(mini, &token, str, &quote);
		// dprintf(2, "var");
		// getchar();
	}
	while (mini->token)
	{
		dprintf(1, "|%d|%s|\n", mini->token->type, mini->token->str);
		mini->token = mini->token->next;
	}
	return (mini->sig.status);
}

int	main(int ac, char **argv)
{
	int		err;
	char	*str = argv[1];
	t_mini	*mini;

	(void) ac;
	mini = malloc(sizeof(t_mini));
	mini->sig.status = lexer(mini, str);
	return (mini->sig.status);
}