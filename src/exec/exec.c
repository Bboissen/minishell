/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 16:53:20 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Count the number of tokens in a list starting from a given token.
 * @param {t_token*} token - The starting token.
 * @return {int} - Returns the count of tokens.
 */
static int	count_tokens(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 2;
	tmp = token->next;
	while (tmp && tmp->type < TRUNC)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

/**
 * Create a command table from a list of tokens.
 * @param {t_token*} token - The starting token.
 * @return {char**} - Returns a dynamically allocated array of strings representing the command.
 */
static char	**cmd_tab(t_token *token)
{
	t_token	*tmp;
	char	**tab;
	int		size;
	int		i;

	if (!token)
		return (NULL);
	size = count_tokens(token);
	tab = malloc(sizeof(char *) * size);
	if (!tab)
		return (NULL);
	tmp = token->next;
	tab[0] = token->str;
	i = 1;
	while (tmp && tmp->type < TRUNC)
	{
		tab[i++] = token->str;
		tmp = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

/**
 * Expand and execute a command.
 * @param {char**} cmd - The command to execute.
 * @param {t_mini*} mini - The main structure of the shell.
 */
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

/**
 * Execute a command.
 * @param {t_mini*} mini - The main structure of the shell.
 */
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
