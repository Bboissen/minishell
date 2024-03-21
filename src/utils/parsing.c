/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:48 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/18 17:44:27 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char *line, int i)
{
	if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (TRUE);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (TRUE);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (TRUE);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
		&& line[i + 2] && line[i + 2] == '>')
		return (TRUE);
	return (FALSE);
}

int	quotes(char *line, int index)
{
	int	i;
	int	quote_open;

	i = 0;
	quote_open = 0;
	while (line[i] && i <= index)
	{
		if (i > 0 && line[i - 1] == '\\')
			continue ;
		else if (quote_open == 0 && line[i] == '\"')
			quote_open = 1;
		else if (quote_open == 0 && line[i] == '\'')
			quote_open = 2;
		else if (quote_open == 1 && line[i] == '\"')
			quote_open = 0;
		else if (quote_open == 2 && line[i] == '\'')
			quote_open = 0;
		i++;
	}
	return (quote_open);
}

int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token, NOSKIP);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
			return (1);
	}
	return (0);
}

int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI")
			&& (!token->next || is_types(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			if (token->next)
				ft_putstr_fd(token->next->str, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			return (mini->ret = 258, FALSE);
		}
		if (is_types(token, "PE")
			&& (!token->prev || !token->next || is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			return (mini->ret = 258, FALSE);
		}
		token = token->next;
	}
	return (TRUE);
}
