/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:33:41 by bboissen          #+#    #+#             */
/*   Updated: 2024/03/22 13:22:40 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*<infile1 grep a >outfile1 | <infile1 cat >outfile2 | <infile2 sed "s/And/But/" | grep But | cat >outfile3 | cat*/

// syntax error if sequential spe charact (except $), empty string or spaces, 

// < >in"f"il'e2' grep t
int		is_spechar(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '$')
		return (1);
	return (0);
}

int is_valid_sequence(char c1, char c2) {
    if (c1 == '<' && (c2 == '<' || c2 == '$'))
		return 1;
    if (c1 == '>' && (c2 == '<' || c2 == '$'))
		return 1;
    return 0;
}

void	token_typer(char *token, char **spe, t_token *tok)
{
	if (*token == '|')
		tok->type = PIPE;
	else if (*token == '>' && *(token + 1) && *(token + 1) == '>')
		tok->type = APPEND;
	else if (*token == '>')
		tok->type = TRUNC;
	else if (*token == '<')
		tok->type = INPUT;
	else if (*token == '$')
		tok->type = VAR;
}
char	*tokenizer(char *str, char **spe, t_token *tok)
{
	static char	*token;
	char		*start;
	char		c;

	if (str)
		token = str;
	if (!token)
		return (NULL);
	while (ft_isspace(*token))
		token++;
	if (!*token)
	{
		token = NULL;
		return (NULL);
	}
	start = token;
	while (*token && !is_spechar(token) && !ft_isspace(*token))
	{
		if (*token == '\'' || *token == '"')
		{
			c = *token;
			while (*token && *token != c)
				token++;
		}
		else if (is_spechar(*token))
		{
			token_typer(token, spe, tok);
			if (tok->type == VAR || tok->type == APPEND || tok->type == TRUNC || tok->type == INPUT)
				while (*token && !ft_isspace(*token))
					token++;
				
		}
		else	
			token++;
	}
	token_typer(token, spe, tok);
	if (*token)
	{
		*token = '\0';
		token++;
	}
	return (start);
}

int main(void)
{
	char **spe = {"|", ">", ">>", "<", "$"};
	return (0);
}