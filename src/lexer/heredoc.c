/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:12:49 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/24 17:31:02 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	my_rand(t_mini *mini);

 // protected
char	*random_file(t_mini *mini)
{
	char			*file;
	char			*tmp;
	unsigned int	rand;
	unsigned int	seed;
	int				i;

	i = 0;
	rand = 0;
	while (i++ < 9)
	{
		seed = my_rand(mini);
		rand = rand * 10 + seed;
	}
	tmp = ft_itoa(rand);
	if (!tmp)
		return (NULL);
	file = ft_strjoin("/tmp/", tmp);
	free(tmp);
	return (file);
}

 // protected
static unsigned int	my_rand(t_mini *mini)
{
	static unsigned int	seed;
	int					fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (error_manager(mini, OPEN, "open", "/dev/urandom"));
	if (read(fd, &seed, sizeof(seed)) != sizeof(seed))
		return (error_manager(mini, OPEN, "read", "/dev/urandom"));
	close(fd);
	seed = (3565867 * seed + 12345) % (1U << 31);
	return (seed % 10);
}

void	heredoc(t_mini *mini)
{
	t_token	*token;
	char	*file;
	char	*line;
	int		fd;

	token = mini->h_token;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			token = token->next;
			while (token && token->join == JOIN)
			{
				token = list_join(mini, token);
				if (token->next)
					token = token->next;
				else
					break ;
			}
			file = random_file(mini);
			if (!file)
				error_manager(mini, MALLOC, NULL, NULL);
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
				error_manager(mini, OPEN, "open", file);
			readline_setup(mini, &line, "heredoc");
			while (line && ft_strcmp(line, token->str))
			{
				while (*line)
				{
					if (*line == '$')
						line = expand_line(mini, line + 1, fd);
					else
						write(fd, line++, 1);
				}
				write(fd, "\n", 1);
				readline_setup(mini, &line, "heredoc");
			}
			close(fd);
			free(token->str);
			token->str = file;
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
	write(fd, var, ft_strlen(var));
	*str = end;
	return (str++);
}
