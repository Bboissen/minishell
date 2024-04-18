/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:07 by bbsn              #+#    #+#             */
/*   Updated: 2024/04/11 18:10:25 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if builtin like export, delete cmd struct and create new one
void	parser(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		flag;

	token = mini->token_h;
	init_cmd(mini, &cmd);
	flag = 0;
	while (token)
	{
		if (token->type == INPUT || token->type == HEREDOC)
			check_read(&cmd, token->next->str);
		else if (token->type == APPEND || token->type == TRUNC)
			check_write(&cmd, token->next->str);
		else if (token->type == STR && flag == 0)
			check_cmd(&cmd, token->next->str, &flag);
		else if (token->type == PIPE)
		{
			flag = 0;
			new_cmd(mini, &cmd);
			init_cmd(mini, &cmd);
		}
	}
}
static void	check_read()
{

}

static void	check_write()
{

}

//check builtin	
static void	check_cmd()
{

}