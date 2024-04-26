/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:09:58 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 18:20:25 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print the current working directory.
 * @return {int} - Returns SUCCESS if the current working directory was 
 * printed successfully, ERROR otherwise.
 */
int	mini_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		return (ft_printfd(1, "%s", cwd), SUCCESS);
	else
		return (ERROR);
}
