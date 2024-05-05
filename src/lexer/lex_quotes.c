/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 10:24:11 by talibabtou        #+#    #+#             */
/*   Updated: 2024/05/05 12:08:07 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*s_quote_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	t_type	options[3];

	if (!str || *str != '\'' || *quote != 0)
		return (str);
	while (*str == '\'')
	{
		str++;
		*quote = ((*quote) + 1) % 2;
	}
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
	if (*quote == 0 && *str && mini->token && is_spe_builtin(mini->token))
		return (new_token(mini, "\0", options), str);
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

char	*d_quote_handler(t_mini *mini, char *str, int *quote)
{
	char	*start;
	char	end;
	t_type	options[3];

	if (*quote == 0 && (!str || *str != '"' ))
		return (str);
	while (*str == '"')
	{
		str++;
		*quote = ((*quote) + 1) % 2;
	}
	options[0] = STR;
	options[1] = 0;
	options[2] = 0;
	if (*quote == 0 && *str && mini->token && is_spe_builtin(mini->token))
		return (new_token(mini, "\0", options), str);
	else if (*quote == 0)
		return (str);
	start = str;
	while (*str != '"' && *str != '$')
		str++;
	end = *str;
	*str = '\0';
	if (end == '$' || ((*(str + 1) && is_spechar(*(str + 1))
				!= 2 && !ft_isspace(*(str + 1)))))
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

/**
 * @brief Checks if there are odd number of quotes in the string.
 * 
 * @param str Input string.
 * @return Returns TRUE if there are odd number of quotes,
 * otherwise returns FALSE.
 */
int	odd_quote(char *str)
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
