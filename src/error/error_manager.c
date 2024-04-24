/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:51:27 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/24 07:43:09 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_manager(t_mini *mini, int err, char *fct, char *str)
{
	if (mini && err == MALLOC)
	{
		dprintf(STDERR_FILENO, "%s: memory allocation failed\n", mini->name);
		return (clean_exit(mini));
	}
	else if (fct)
	{
		dprintf(STDERR_FILENO, "%s: ", mini->name);
		dprintf(STDERR_FILENO, "%s: ", fct);
		perror(str);
		return (clean_exit(mini));
	}
	return (clean_exit(mini));
}
