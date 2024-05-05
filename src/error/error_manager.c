/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:51:27 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/05 18:46:03 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Global error manager.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param err Error code indicating the type of error.
 * @param fct Pointer to the function where the error occurred.
 * @param str Pointer to the string where the error occurred.
 * @return {int} - Calls the clean_exit function to exit the shell.
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
