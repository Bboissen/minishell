/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:32 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/26 16:53:06 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of separators in a line.
 * 
 * @param line The line of text to count separators in.
 * @return int The number of separators in the line.
 */
int	count_separators(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Allocates space for a new line with extra space for separators.
 * 
 * @param line The original line of text.
 * @return char* A pointer to the newly allocated space, or NULL if allocation failed.
 */
char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		len;

	count = count_separators(line);
	len = strlen(line);
	new = malloc(sizeof(char) * (len + 2 * count + 1));
	if (!new)
		return (NULL);
	return (new);
}

/**
 * @brief Adds spaces around separators in a line.
 * 
 * @param line The original line of text.
 * @return char* The new line with spaces added, or NULL if allocation failed.
 */
char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

/**
 * @brief Checks if a line has any unclosed quotes.
 * 
 * @param mini The main structure of the program.
 * @param line The line of text to check.
 * @return int Returns 1 if there are unclosed quotes, 0 otherwise.
 */
int	quote_check(t_mini *mini, char **line)
{
	if (quotes(*line, INT_MAX))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->sig.status = 2;
		mini->token = NULL;
		return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief Parses a line of input and processes the resulting tokens.
 * 
 * @param mini The main structure of the program.
 */
void	parse(t_mini *mini)
{
	char	*line;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	if (readline("\033[32;1m minishell ▸ \033[0m"))
		return ;
	if (mini->sig.sigint == 1)
		mini->sig.status = mini->sig.status;
	if (quote_check(mini, &line))
		return ;
	line = space_line(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	mini->token = get_tokens(line);
	ft_memdel(line);
	squish_args(mini);
	process_tokens(mini);
}
