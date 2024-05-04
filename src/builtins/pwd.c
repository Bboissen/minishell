/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:09:58 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 11:45:22 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the current working directory.
 * 
 * @return {int} - Returns SUCCESS if the current working directory
 * was printed successfully, ERROR otherwise.
 */
int	mini_pwd(t_mini *mini, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		fd;

	(void)mini;
	if (cmd->fd[1] != -1)
		fd = cmd->fd[1];
	else
		fd = STDOUT_FILENO;
	if (getcwd(cwd, PATH_MAX))
		return (ft_printfd(fd, "%s\n", cwd), SUCCESS);
	else
	{
		ft_printfd(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		return (ERROR);
	}
}
