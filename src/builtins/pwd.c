/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:09:58 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/24 17:23:17 by gdumas           ###   ########.fr       */
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

	(void)mini;
	if (getcwd(cwd, PATH_MAX))
		return (ft_printfd(STDOUT_FILENO, "%s\n", cwd), SUCCESS);
	else
		return (ERROR);
}
