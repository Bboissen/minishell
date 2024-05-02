/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:43 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/29 16:36:37 by bboissen         ###   ########.fr       */
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
				// perror
				current = current->next;
			}
		}
		current = current->next;
	}
}

/**
 * @brief Calculate the size of the command.
 * 
 * @param h_cmd The head of the command list.
 * @return {int} The size of the command list.
 */
int	cmd_size(t_cmd *h_cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = h_cmd;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
