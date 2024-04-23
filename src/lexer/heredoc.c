/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbsn <bbsn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:12:49 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/23 10:02:06 by bbsn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	my_rand(t_mini *mini);
 // protected
char	*random_file(t_mini *mini)
{
	char 			*file;
	char 			*tmp;
	unsigned int	rand;
	unsigned int	seed;
	int				i;

	i = 0;
	rand = 0;
	while (i++ < 9)
	{
		seed = my_rand(mini);
		rand = rand * 10 + my_rand(mini);
	}
	tmp = ft_itoa(rand); //protected
	if (!tmp)
		return (NULL);
	file = ft_strjoin("/tmp/", tmp); //protected
	free(tmp);
	return (file);
}
 // protected
static unsigned int	my_rand(t_mini *mini)
{
	static unsigned int	seed;
	int					fd;

	fd = open("/dev/random", O_RDONLY); // protected
	if (fd == -1) 
		return (error_manager(mini, OPEN, "open", "/dev/random")); // protected
	if (read(fd, &seed, sizeof(seed)) != sizeof(seed))
		return (error_manager(mini, OPEN, "read", "/dev/random")); // protected
	close(fd);
	seed = (3565867 * seed + 12345) % (1U << 31);
	return (seed % 10);
}
int	heredoc(t_mini *mini)
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
				token = list_join(mini, token); //protected
				if(token->next)
					token = token->next;
				else
					break;
			}
			file = random_file(mini);
			if (!file)
				return (error_manager(mini, MALLOC, NULL, NULL));  // protected
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
				return (error_manager(mini, OPEN, "open", file));  // protected
			readline_setup(mini, &line, "heredoc");  // protected
			while (ft_strcmp(line, token->str))
			{
				while (*line)
				{
					if (*line == '$')
						line = expand_line(mini, line + 1, fd);  // protected
					else
						write(fd, line++, 1);
				}
				write(fd, "\n", 1);
				readline_setup(mini, &line, "heredoc");  // protected
			}
			close(fd);  // protected
			token->str = file;
		}
		token = token->next;
	}
	return (0);
}
 // protected
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
	var = expand_token(&mini, start);  // protected
	write(fd, var, ft_strlen(var));
	*str = end;
	return (str++);
}
