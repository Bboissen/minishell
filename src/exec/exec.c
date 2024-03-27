/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 13:42:20 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_token *start)
{
	int		count;
	t_token	*token;

	count = 2;
	token = start->next;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		count++;
	}
	return (count);
}

char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		size;
	int		i;

	if (!start)
		return (NULL);
	size = count_tokens(start);
	tab = malloc(sizeof(char *) * size);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

static void	expand_and_exec_cmd(char **cmd, t_mini *mini)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
		cmd[i] = expansions(cmd[i], mini->env, mini->sig.status);
	if (cmd && ft_strcmp(cmd[0], "exit") == SUCCESS
		&& has_pipe(mini->token) == SUCCESS)
		mini_exit(mini, cmd);
	else if (cmd && is_builtin(cmd[0]))
		mini->sig.status = exec_builtin(cmd, mini);
	else if (cmd)
		mini->sig.status = exec_bin(cmd, mini->env, mini);
}

void	exec_cmd(t_mini *mini)
{
	char	**cmd;

	cmd = cmd_tab(mini->token);
	expand_and_exec_cmd(cmd, mini);
	free_tab(cmd);
	ft_close(mini->cmd->pipe[0]);
	ft_close(mini->cmd->pipe[1]);
	mini->cmd->pipe[0] = -1;
	mini->cmd->pipe[1] = -1;
}
