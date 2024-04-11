/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/11 17:30:10 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*adapt for t_env*/
/**
 * Create a command table from a list of tokens.
 * @param {t_token*} token - The starting token.
 * @return {char**} - Returns a dynamically allocated array 
 * of strings representing the command.
 */
static char	**cmd_tab(t_env *env)
{
	t_token	*tmp;
	char	**tab;
	int		size;
	int		i;

	if (!env)
		return (NULL);
	size = lst_size(env);
	tab = malloc(sizeof(char *) * size);
	if (!tab)
		return (NULL);
	tmp = env->next;
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

/*
 * Create a pipe and fork a new process.
 * The child process reads from the pipe and the parent writes to it.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns 2 if it's the child process, 1 if it's the parent.
 */
int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->cmd->pipe[0] = pipefd[0];
		mini->parent = 0;
		mini->token->skip = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->cmd->pipe[1] = pipefd[1];
		mini->last = 0;
		return (1);
	}
}
