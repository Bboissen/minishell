/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:51:27 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/06 16:52:59 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Global error manager.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param error The error code.
 * @param arg The argument that caused the error.
 * @return {int} - Returns a call to clean_exit.
 */
int	error_manager(t_mini *mini, int err, char *fct, char *str)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = err;
	if (mini && err == MALLOC)
	{
		ft_printfd(STDERR_FILENO, "%s: memory allocation failed\n", mini->name);
		return (clean_exit(mini));
	}
	else if (fct)
	{
		ft_printfd(STDERR_FILENO, "%s: %s: %s\n",
			mini->name, str, strerror(err));
		return (clean_exit(mini));
	}
	return (clean_exit(mini));
}
