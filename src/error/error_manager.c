/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:51:27 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/25 17:01:03 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//bash: export: `te@st=2': not a valid identifier

int	error_manager(t_mini *mini, int err, char *fct, char *str)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = err;
	if (mini && err == MALLOC)
	{
		ft_printfd(STDERR, "%s: memory allocation failed\n", mini->name);
		return (clean_exit(mini));
	}
	else if (fct)
	{
		ft_printfd(STDERR, "%s: ", mini->name);
		ft_printfd(STDERR, "%s: ", str);
		perror(fct);
		return (clean_exit(mini));
	}
	return (clean_exit(mini));
}
