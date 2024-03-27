/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:43 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/26 15:10:44 by gdumas           ###   ########.fr       */
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
	dup2(mini->cmd->in, STDIN);
	dup2(mini->cmd->out, STDOUT);
}

/**
 * @brief Closes the file descriptors associated with the current command.
 * 
 * @param mini The main structure of the program.
 */
void	close_fds(t_mini *mini)
{
	ft_close(mini->cmd->fd[0]);
	ft_close(mini->cmd->fd[1]);
	ft_close(mini->cmd->pipe[0]);
	ft_close(mini->cmd->pipe[1]);
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
	mini->cmd->pipe[0] = -1;
	mini->cmd->pipe[1] = -1;
}
