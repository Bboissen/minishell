/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 14:58:11 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **env)
{
	t_mini	*mini;
	char	*rl;

	if (ac != 1)
		return (ERROR);
	init_mini(mini, env, av[0]);
	while (!mini->sig.exit)
	{
		readline_setup(&rl, &mini, av[0]);
		heredoc(mini);
		lexer(mini, rl);
		expand_join(mini);
		parser(mini);
		if (mini->cmd)
			exec_cmd(mini);
		reinit(mini, rl);
	}
	return (clean_exit(&mini));
}
