/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:24:24 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 09:40:59 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	my_rand(t_mini *mini);
static void			expand_inside(t_mini *mini, t_token *token, int fd);

/**
 * @brief Hook function for readline library to handle interrupts.
 * 
 * @return {int} Returns SUCCESS constant.
 */
int	readline_hook(void)
{
	rl_done = 0;
	if (get_sig()->status == INTERUPT)
	{
		rl_done = 1;
	}
	return (SUCCESS);
}

/**
 * @brief Generates a random file name in the /tmp directory.
 * 
 * @param mini Pointer to the mini shell structure.
 * @return {char *} - Returns a string containing the path to the random file.
 */
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

/**
 * @brief Generates a random number using /dev/urandom as a seed.
 * 
 * @param mini Pointer to the mini shell structure.
 * @return {unsigned int} - Returns a random number.
 */
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

/**
 * @brief Expands the heredoc token and its next token if it exists.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param token Double pointer to the token structure.
 * @param fd File descriptor.
 */
void	expand_heredoc(t_mini *mini, t_token **token, int fd)
{
	expand_inside(mini, *token, fd);
	if ((*token)->next)
	{
		expand_inside(mini, (*token)->next, fd);
	}
}

/**
 * @brief Expands the token if its expand flag is set.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param token Pointer to the token structure.
 * @param fd File descriptor.
 */
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
