/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:42:56 by talibabtou        #+#    #+#             */
/*   Updated: 2024/04/24 16:08:23 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_err(t_mini *mini, int error, char *arg)
{
	int	i;

	(void)mini;
	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR_FILENO);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write((STDERR_FILENO), &arg[i], 1);
		i++;
	}
	write((STDERR_FILENO), "\n", 1);
	return (ERROR);
}
