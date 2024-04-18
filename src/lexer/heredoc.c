/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:12:49 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/18 10:40:20 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ADAPT HEREDOC WITH JOIN
#include "minishell.h"

static unsigned int	my_rand(void);

char	*random_file(void)
{
	char			*file;
	char			*tmp;
	unsigned int	rand;
	int				i;

	i = 0;
	rand = 0;
	while (i++ < 9)
		rand = rand * 10 + my_rand();
	tmp = ft_itoa(rand);
	if (!tmp)
		return (NULL);
	file = ft_strjoin("/tmp/", tmp);
	free(tmp);
	return (file);
}

static unsigned int	my_rand(void)
{
	static unsigned int	seed;
	int					fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (read(fd, &seed, sizeof(seed)) != sizeof(seed))
	{
		perror("read");
		exit(1);
	}
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
			file = random_file();
			if (!file)
			{
				return ;
			}
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (fd == -1)
			{
				perror("open");
				free(file);
				return ;
			}
			readline_setup(&line, "heredoc");
			if (line)
			{
				while (ft_strcmp(line, token->next->str))
				{
					while (*line)
					{
						if (*line == '$')
							line = expand_line(mini, line + 1, fd);
						else
							write(fd, line++, 1);
					}
					write(fd, "\n", 1);
					readline_setup(&line, "heredoc");
				}
			}
			close(fd);
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
