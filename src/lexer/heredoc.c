/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:12:49 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/03 17:36:57 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int readline_hook()
{
	rl_done = 0;
	if (get_sig()->status == INTERUPT)
	{
		rl_done = 1;
	}
	return (0);
}
static unsigned int	my_rand(t_mini *mini);
static void	expand_heredoc(t_mini *mini, t_token **token, int fd);
//protected random iteration
char	*random_file(t_mini *mini)
{
	char 			*file;
	char 			*tmp;
	unsigned int	rand;
	int				i;
	// static int j =0;

	i = 0;
	rand = 0;
	while (i++ < 9)
	{
		rand = rand * 10 + my_rand(mini);
	}
	tmp = ft_itoa(rand); //protected random iteration
	if (!tmp)
		return (NULL);
	file = ft_strjoin("/tmp/", tmp); //protected random iteration
	free(tmp);
	return (file);
}
//protected
static unsigned int	my_rand(t_mini *mini)
{
	static unsigned int	seed;
	int					fd;

	fd = open("/dev/urandom", O_RDONLY); //protected
	if (fd == -1) 
		return (error_manager(mini, errno, "open", "/dev/urandom")); //protected
	if (read(fd, &seed, sizeof(seed)) != sizeof(seed))
		return (error_manager(mini, errno, "read", "/dev/urandom")); //protected
	close(fd);
	seed = (3565867 * seed + 12345) % (1U << 31);
	return (seed % 10);
}

//to protect
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
			token->str = random_file(mini); //protected random iteration
			if (!token->str)
				error_manager(mini, MALLOC, NULL, NULL);
			fd = open(token->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
				error_manager(mini, errno, "open", token->str);
			token = token->next;
			while (token && token->join == JOIN)
			{
				expand_heredoc(mini, &token, fd); //protected random iteration
				token = list_join(token); //protected random iteration
				if (!token)
				{
					close(fd);
					error_manager(mini, MALLOC, NULL, NULL);
				}
			}
			rl_event_hook = readline_hook;
			readline_setup(mini, &line, "heredoc");
			p_line = line;
			while (line && ft_strcmp(line, token->str) && get_sig()->status != INTERUPT)
			{
				while (*line)
				{
					if (*line == '$')
						line = expand_line(mini, line + 1, fd); //to protect
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
//to protect
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
	var = expand_token(&mini, start); //to protect
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

//to protect
static void	expand_heredoc(t_mini *mini, t_token **token, int fd)
{
	char	*new_str;

	if ((*token)->expand == EXPAND)
	{
		new_str = ft_strjoin("$", (*token)->str); //to protect
		if (!new_str)
		{
			close(fd);
			error_manager(mini, MALLOC, NULL, NULL);
		}
		free((*token)->str);
		(*token)->str = new_str;
		(*token)->expand = 0;
	}
	if ((*token)->next->expand == EXPAND)
	{
		new_str = ft_strjoin("$", (*token)->next->str); //to protect
		if (!new_str)
		{
			close(fd);
			error_manager(mini, MALLOC, NULL, NULL);
		}
		free((*token)->next->str);
		(*token)->next->str = new_str;
		(*token)->next->expand = 0;
	}
}
