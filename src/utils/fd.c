/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:43 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/16 13:59:24 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes a file descriptor if it is valid.
 * 
 * @param fd The file descriptor to close.
 */
void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

/**
 * @brief Resets the standard input and output to the command's input and output.
 * 
 * @param mini The main structure of the program.
 */
void	reset_std(t_mini *mini)
{
	dup2(mini->cmd->fd[0], STDIN);
	dup2(mini->cmd->fd[1], STDOUT);
}

/**
 * @brief Closes the file descriptors associated with the current command.
 * 
 * @param mini The main structure of the program.
 */
void	close_fds(int *fd)
{
	if (fd[0] != -1)
	{
		ft_close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		ft_close(fd[1]);
		fd[1] = -1;
	}
}

/**
 * @brief Closes the file descriptors associated with the current 
 * command and resets them to -1.
 * 
 * @param mini The main structure of the program.
 */
void	delete_heredoc(t_mini *mini)
{
	t_token	*token;

	token = mini->h_token;
	while (token)
	{
		if (token->type == HEREDOC)
			unlink(token->str);
		token = token->next;
	}
}
