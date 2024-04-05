/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:33:41 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/05 17:09:38 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	odd_quote(char *str)
{
	int		i;
	int		flag;
	int		s_quote;
	int		d_quote;

	i = 0;
	flag = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && d_quote != 1)
			s_quote = ++s_quote % 2;
		else if (str[i] == '"' && s_quote != 1)
			d_quote = ++d_quote % 2;
		i++;
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
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 93) || (c >= 123 && c <= 125))
		return (1);
	else
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
	printf("\n------------------------------------------\n");
	printf("|type\t|%-20s|join|expand|\n", "string");
	printf("------------------------------------------\n");
	while (str && *str /*&& mini->sig.exit == 0*/)
	{
		while (str && quote == 0 && *str && is_space(*str))
		{
			str++;
			if (token && (token)->join == JOIN)
			{
				printf("token = %d\n", (token)->join);
				(token)->join = 0;
			}
		}
		str = syntax_check(mini, &token, str, &quote);
		str = string_handler(mini, &token, str, &quote);
		str = s_quote_handler(mini, &token, str, &quote);
		str = d_quote_handler(mini, &token, str, &quote);
		str = var_handler(mini, &token, str, &quote);
	}
	if (token && !token->str)
		return (printf("bash: syntax error near unexpected token `newline'\n"));
	if (token && (token)->join == JOIN)
			(token)->join = 0;
	while (mini->token)
	{
		dprintf(1, "|%d\t|%-20s|%-4d|%d|\n", mini->token->type, mini->token->str, mini->token->join, mini->token->expand);
		mini->token = mini->token->next;
	}
	return (mini->sig.status);
}

int	main(void)
{
	int		err;
	char *rl = NULL;
	char *pwd;
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	while (!rl || rl[0] != 'z')
	{
		rl = readline("Michel > ");
		add_history(rl);
		if (rl[0] == 'c')
			rl_clear_history();
		if (rl[0] == 'p')
		{
			pwd = getcwd(NULL, 0);
			printf("%s\n", pwd);
		}
		mini->sig.status = lexer(mini, rl);
		rl_on_new_line();
		free(rl);
		printf("\n\n\n");
	}
	return (mini->sig.status);
}
