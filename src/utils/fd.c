/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbsn <bbsn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:43 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/05 23:41:45 by bbsn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes file descriptors if they are not standard input or output.
 * 
 * @param fd An array of file descriptors to be closed.
 */
void	close_fds(int *fd)
{
	if (fd[0] != -1)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		close(fd[1]);
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
	t_token	*current;

	current = mini->h_token;
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			if (unlink(current->next->str) == -1)
			{
				error_manager(mini, errno, "unlink", current->next->str);
				current = current->next;
			}
		}
		current = current->next;
	}
}

/**
 * @brief Sets the file descriptor for the command.
 * 
 * @param cmd A pointer to the command structure.
 * @return {int} - The file descriptor to be used for the command.
 */
int	set_fd(t_cmd *cmd)
{
	if (cmd->fd[1] != -1)
		return (cmd->fd[1]);
	else
		return (STDOUT_FILENO);
}
