/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:43 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/23 11:27:56 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Closes file descriptors if they are not standard input or output.
 * 
 * This function checks if the file descriptors are not standard input (0) or 
 * standard output (1), and if they are not, it closes them and sets them to -1.
 * 
 * @param fd An array of file descriptors to be closed.
 */
void	close_fds(int *fd)
{
	if (fd[0] != -1 && fd[0] != STDIN_FILENO)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1 && fd[1] != STDOUT_FILENO)
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
				// perror
				current = current->next;
			}
		}
		current = current->next;
	}
}
