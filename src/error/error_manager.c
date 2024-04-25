/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:51:27 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/25 09:30:55 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//bash: export: `te@st=2': not a valid identifier

int	error_manager(t_mini *mini, int err, char *fct, char *str)
{
	if (mini && err == MALLOC)
	{
		ft_printfd(STDERR, "%s: memory allocation failed\n", mini->name);
		return (clean_exit(mini));
	}
	else if (fct)
	{
		ft_printfd(STDERR, "%s: ", mini->name);
		ft_printfd(STDERR, "%s: ", fct);
		perror(str);
		return (clean_exit(mini));
	}
	return (clean_exit(mini));
}
