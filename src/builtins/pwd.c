/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:09:58 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/01 11:12:12 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the current working directory.
 * 
 * @return {int} - Returns SUCCESS if the current working directory was 
 * printed successfully, ERROR otherwise.
 */
int	mini_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	int		fd;

	if (mini->cmd->fd[1] != -1)
		fd = mini->cmd->fd[1];
	else
		fd = STDOUT_FILENO;
	if (getcwd(cwd, PATH_MAX))
		return (ft_printfd(fd, "%s\n", cwd), SUCCESS);
	else
		return (ERROR);
}
