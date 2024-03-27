/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:23 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 13:34:37 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error(t_mini *mini)
{
	ft_printfd(STDERR, "minishell: %s: No such file or directory\n",
		mini->token->str);
	mini->sig.status = 1;
	mini->token->skip = 1;
}

void	redir(t_mini *mini, t_token *token)
{
	ft_close(mini->cmd->fd[1]);
	if (token->type == TRUNC)
		mini->cmd->fd[1] = open(token->str, O_CREAT
				| O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->cmd->fd[1] = open(token->str, O_CREAT
				| O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->cmd->fd[1] == -1)
	{
		handle_error(mini);
		return ;
	}
	dup2(mini->cmd->fd[1], STDOUT);
}

void	input(t_mini *mini)
{
	ft_close(mini->cmd->fd[0]);
	mini->cmd->fd[0] = open(mini->token->str, O_RDONLY, S_IRWXU);
	if (mini->cmd->fd[0] == -1)
	{
		handle_error(mini);
		return ;
	}
	dup2(mini->cmd->fd[0], STDIN);
}

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
