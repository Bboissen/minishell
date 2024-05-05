/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:12:49 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/05 16:24:18 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handle_file_and_token(t_mini *mini, t_token **token, int *fd);
void		handle_line_reading_and_expansion(t_mini *mini,
				t_token *token, char **line, int fd);
void		handle_cleanup_and_error_handling(t_mini *mini,
				t_token *token, char *line, int fd);
static char	*expand_line(t_mini *mini, char *str, int fd);

/**
 * @brief Handles the heredoc functionality in the shell.
 * 
 * @param mini Pointer to the mini structure.
 */
void	heredoc(t_mini *mini)
{
	t_token	*token;
	char	*line;
	int		fd;

	token = mini->h_token;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			handle_file_and_token(mini, &token, &fd);
			rl_event_hook = readline_hook;
			readline_setup(mini, &line, "heredoc");
			handle_line_reading_and_expansion(mini, token, &line, fd);
			if (line)
				ft_memdel(line);
			rl_event_hook = NULL;
			handle_cleanup_and_error_handling(mini, token, line, fd);
		}
		token = token->next;
	}
}

/**
 * @brief Handles the file and token operations for the heredoc functionality.
 * 
 * @param mini Pointer to the mini structure.
 * @param token Double pointer to the token structure.
 * @param fd Pointer to the file descriptor.
 */
void	handle_file_and_token(t_mini *mini, t_token **token, int *fd)
{
	(*token)->str = random_file(mini);
	if (!(*token)->str)
		error_manager(mini, MALLOC, NULL, NULL);
	*fd = open((*token)->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
		error_manager(mini, errno, "open", (*token)->str);
	*token = (*token)->next;
	if ((*token)->expand == EXPAND)
		expand_heredoc(mini, token, *fd);
	while (*token && ((*token)->join == JOIN))
	{
		expand_heredoc(mini, token, *fd);
		*token = list_join(*token);
		if (!*token)
		{
			close(*fd);
			error_manager(mini, MALLOC, NULL, NULL);
		}
	}
}

/**
 * @brief Handles the line reading and expansion for the heredoc functionality.
 * 
 * @param mini Pointer to the mini structure.
 * @param token Pointer to the token structure.
 * @param line Double pointer to the line string.
 * @param fd File descriptor.
 */
void	handle_line_reading_and_expansion(t_mini *mini,
			t_token *token, char **line, int fd)
{
	char	*p_line;

	p_line = *line;
	while (*line && ft_strcmp(*line, token->str)
		&& get_sig()->status != INTERUPT)
	{
		printf("line = %s %s\n", *line, token->str);
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
}

/**
 * @brief Handles the cleanup and error handling for the heredoc functionality.
 * 
 * @param mini Pointer to the mini structure.
 * @param token Pointer to the token structure.
 * @param line Pointer to the line string.
 * @param fd File descriptor.
 */
void	handle_cleanup_and_error_handling(t_mini *mini,
			t_token *token, char *line, int fd)
{
	close(fd);
	if (get_sig()->status == INTERUPT)
	{
		rl_done = 0;
		free_token(&mini->h_token);
		return ;
	}
	if (!line)
		return (lexer_err(mini, token->str, END, 0));
	free(token->str);
	token->str = token->prev->str;
	token->prev->str = NULL;
}

/**
 * @brief Expands the line for the heredoc functionality.
 * 
 * @param mini Pointer to the mini structure.
 * @param str Pointer to the string to be expanded.
 * @param fd File descriptor.
 * @return {char *} - Returns the expanded string.
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
