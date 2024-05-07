/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:12:49 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/07 14:06:10 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		file_and_token(t_mini *mini, t_token **token, int fd);
static char		*line_reading_and_expansion(t_mini *mini,
					t_token *token, char **line, int fd);
static int		cleanup_and_error_handling(t_mini *mini,
					t_token *token, char *line, int fd);
static char		*expand_line(t_mini *mini, char *str, int fd);

/**
 * @brief Heredoc functionality to prompt in.
 * 
 * @param mini Pointer to the mini shell structure.
 */
void	heredoc(t_mini *mini)
{
	t_token	*token;
	char	*line;
	char	*p_line;
	int		fd;

	token = mini->h_token;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			get_sig()->status = 0;
			fd = file_and_token(mini, &token, fd);
			rl_event_hook = readline_hook;
			readline_setup(mini, &line, "heredoc");
			p_line = line_reading_and_expansion(mini, token, &line, fd);
			if (p_line)
				ft_memdel(p_line);
			rl_event_hook = NULL;
			if (cleanup_and_error_handling(mini, token, line, fd))
				return ;
		}
		token = token->next;
	}
	mini->token = mini->h_token;
}

/**
 * @brief Handles file and token operations for heredoc.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param token Double pointer to the token structure.
 * @param fd File descriptor.
 * @return {int} - Heredoc file descriptor.
 */
static int	file_and_token(t_mini *mini, t_token **token, int fd)
{
	(*token)->str = random_file(mini);
	if (!(*token)->str)
		error_manager(mini, MALLOC, NULL, NULL);
	fd = open((*token)->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		error_manager(mini, errno, "open", (*token)->str);
	*token = (*token)->next;
	if ((*token)->expand == EXPAND)
		expand_heredoc(mini, token, fd);
	while (*token && ((*token)->join == JOIN))
	{
		expand_heredoc(mini, token, fd);
		*token = list_join(*token);
		if (!*token)
		{
			close(fd);
			error_manager(mini, MALLOC, NULL, NULL);
		}
	}
	return (fd);
}

/**
 * @brief Handles line reading and expansion for heredoc.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param token Pointer to the token structure.
 * @param line Double pointer to the line.
 * @param fd File descriptor.
 * @return {char *} - Pointer to the processed line.
 */
static char	*line_reading_and_expansion(t_mini *mini,
			t_token *token, char **line, int fd)
{
	char	*p_line;

	p_line = *line;
	while (*line && ft_strcmp(*line, token->str)
		&& get_sig()->status != INTERUPT)
	{
		while (**line)
		{
			if (**line == '$')
				*line = expand_line(mini, *line + 1, fd);
			else
				write(fd, (*line)++, 1);
		}
		write(fd, "\n", 1);
		ft_memdel(p_line);
		readline_setup(mini, line, "heredoc");
		p_line = *line;
	}
	return (p_line);
}

/**
 * @brief Expands a line for heredoc.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param str Pointer to the string to expand.
 * @param fd File descriptor.
 * @return {char *} - Pointer to the expanded line.
 */
static char	*expand_line(t_mini *mini, char *str, int fd)
{
	char	*start;
	char	*var;
	char	end;

	start = str;
	while (*str && is_spechar(*str) == 0 && !ft_isspace(*str))
		str++;
	end = *str;
	*str = '\0';
	var = expand_token(&mini, start);
	if (!var)
	{
		close(fd);
		error_manager(mini, MALLOC, NULL, NULL);
	}
	write(fd, var, ft_strlen(var));
	free(var);
	*str = end;
	return (str++);
}

/**
 * @brief Handles cleanup and error handling for heredoc.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param token Pointer to the token structure.
 * @param line Pointer to the line.
 * @param fd File descriptor.
 * @return {int} Status code (ERROR or SUCCESS).
 */
static int	cleanup_and_error_handling(t_mini *mini,
			t_token *token, char *line, int fd)
{
	close(fd);
	if (get_sig()->status == INTERUPT)
	{
		rl_done = 0;
		free_token(&mini->h_token);
		return (ERROR);
	}
	if (!line)
		return (lexer_err(mini, token->str, END, 0), ERROR);
	free(token->str);
	token->str = token->prev->str;
	token->prev->str = NULL;
	return (SUCCESS);
}
