/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:43 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 17:25:09 by gdumas           ###   ########.fr       */
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
		ft_close(fd[0]);
	if (fd[1] != -1)
		ft_close(fd[1]);
}

/**
 * @brief Resets the file descriptors associated with the current command to -1.
 * 
 * @param mini The main structure of the program.
 */
void	reset_fds(t_mini *mini)
{
	mini->cmd->fd[0] = -1;
	mini->cmd->fd[1] = -1;
}

/*delete heredoc function, navigate t_token->type=HEREDOC, unlink token->next->str*/