/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:24:24 by talibabtou        #+#    #+#             */
/*   Updated: 2024/05/05 16:13:59 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	my_rand(t_mini *mini);
static void			expand_inside(t_mini *mini, t_token *token, int fd);

int	readline_hook(void)
{
	rl_done = 0;
	if (get_sig()->status == INTERUPT)
	{
		rl_done = 1;
	}
	return (SUCCESS);
}

char	*random_file(t_mini *mini)
{
	char			*file;
	char			*tmp;
	unsigned int	rand;
	int				i;

	i = 0;
	rand = 0;
	while (i++ < 9)
	{
		rand = rand * 10 + my_rand(mini);
	}
	tmp = ft_itoa(rand);
	if (!tmp)
		return (NULL);
	file = ft_strjoin("/tmp/", tmp);
	free(tmp);
	return (file);
}

static unsigned int	my_rand(t_mini *mini)
{
	static unsigned int	seed;
	int					fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (error_manager(mini, errno, "open", "/dev/urandom"));
	if (read(fd, &seed, sizeof(seed)) != sizeof(seed))
		return (error_manager(mini, errno, "read", "/dev/urandom"));
	close(fd);
	seed = (3565867 * seed + 12345) % (1U << 31);
	return (seed % 10);
}

void	expand_heredoc(t_mini *mini, t_token **token, int fd)
{
	expand_inside(mini, *token, fd);
	if ((*token)->next)
	{
		expand_inside(mini, (*token)->next, fd);
	}
}

static void	expand_inside(t_mini *mini, t_token *token, int fd)
{
	char	*new_str;

	if (token->expand == EXPAND)
	{
		new_str = ft_strjoin("$", token->str);
		if (!new_str)
		{
			close(fd);
			error_manager(mini, MALLOC, NULL, NULL);
		}
		free(token->str);
		token->str = new_str;
		token->expand = 0;
	}
}
