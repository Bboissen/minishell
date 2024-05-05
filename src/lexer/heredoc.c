/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:12:49 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/05 16:08:38 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*expand_line(t_mini *mini, char *str, int fd);

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
			token->str = random_file(mini);
			if (!token->str)
				error_manager(mini, MALLOC, NULL, NULL);
			fd = open(token->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
				error_manager(mini, errno, "open", token->str);
			token = token->next;
			if (token->expand == EXPAND)
				expand_heredoc(mini, &token, fd);
			while (token && (token->join == JOIN))
			{
				expand_heredoc(mini, &token, fd);
				token = list_join(token);
				if (!token)
				{
					close(fd);
					error_manager(mini, MALLOC, NULL, NULL);
				}
			}
			rl_event_hook = readline_hook;
			readline_setup(mini, &line, "heredoc");
			p_line = line;
			while (line && ft_strcmp(line, token->str)
				&& get_sig()->status != INTERUPT)
			{
				printf("line = %s %s\n", line, token->str);
				while (*line)
				{
					if (*line == '$')
						line = expand_line(mini, line + 1, fd);
					else
						write(fd, line++, 1);
				}
				write(fd, "\n", 1);
				ft_memdel(p_line);
				readline_setup(mini, &line, "heredoc");
				p_line = line;
			}
			if (p_line)
				ft_memdel(p_line);
			rl_event_hook = NULL;
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
		token = token->next;
	}
}

char	*expand_line(t_mini *mini, char *str, int fd)
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
