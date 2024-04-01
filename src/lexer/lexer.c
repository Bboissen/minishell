/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:33:41 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/01 12:47:16 by bboissen         ###   ########.fr       */
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


int lexer(t_mini *mini, char *str)
{
	int		err;
	int		i;
	t_token	*token;

	err = odd_quote(str);
	if (err)
		return(lexer_err(QUOTE));
	token = malloc(sizeof(t_token));
	token->prev = NULL;
	token->next = NULL;
	mini->token = token;
	i = 0;
	while(str[i] && mini->sig.exit == 0)
	{
		str = syntax_check(mini, token, str);
		str = string_handler(mini, token, str);
		str = s_quote_handler(mini, token, str);
		str = d_quote_handler(mini, token, str);
		str = var_handler(mini, token, str);
	}
	return (err);
}

int main(void)
{
	int	err;
	char *str = "< >'in\"f\"il'e2' grep t";
	t_mini *mini;
	
	mini = malloc(sizeof(t_mini));
	err = lexer(mini, str);
	return (err);
}