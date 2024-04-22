/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:51:27 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/22 16:36:13 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//bash: export: `te@st=2': not a valid identifier

int	error_manager(t_mini *mini, int err, char *fct, char *str)
{
	if (mini && err == MALLOC)
	{
		dprintf(STDERR, "%s: memory allocation failed\n", mini->name);
		return (clean_exit(mini));
	}
	else if (fct)
	{
		dprintf(STDERR, "%s: ", mini->name);
		dprintf(STDERR, "%s: ", fct);
		perror(str);
		return (clean_exit(mini));
	}
	return (clean_exit(mini));
}
