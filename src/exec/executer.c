/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/30 11:52:24 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_mini *mini, t_cmd *cmd, int *initial_fds)
{
	t_sig	*sig;

	sig = get_sig();
	if (!cmd->out)
		dup2(cmd->fd[1], STDOUT_FILENO);
	close_fds(cmd->fd);
	close_fds(initial_fds);
	if (cmd->builtin == NONE)
		execve(cmd->args[0], cmd->args, env_to_tab(mini));
	else
	{
		exec_builtin(mini);
		exit(sig->status);
	}
}

static pid_t	exec(t_mini *mini, t_cmd *cmd, int *initial_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child(mini, cmd, initial_fds);
	else if (pid > 0)
	{
		if (cmd->fd[0] != -1)
			dup2(cmd->fd[0], STDIN_FILENO);
		close_fds(cmd->fd);
	}
	return (pid);
}

static void	piper(t_mini *mini, t_cmd *cmd, int *initial_fds)
{
	int		pipefd[2];

	while (cmd->next)
	{
		fd_handler(mini, cmd);
		pipe(pipefd);
		cmd->fd[0] = pipefd[0];
		cmd->fd[1] = pipefd[1];
		cmd->pid = exec(mini, cmd, initial_fds);
		cmd = cmd->next;
	}
	fd_handler(mini, cmd);
	cmd->fd[0] = initial_fds[0];
	// cmd->fd[1] = initial_fds[1];
	if (!cmd->out)
		dup2(initial_fds[1], STDOUT_FILENO);
	cmd->pid = exec(mini, cmd, initial_fds);
}

void	cmd_exec(t_mini *mini)
{
	t_cmd	*cmd;
	t_sig	*sig;
	int		initial_fds[2];

	sig = get_sig();
	sig->working = TRUE;
	cmd = mini->h_cmd;
	initial_fds[0] = dup(STDIN_FILENO);
	initial_fds[1] = dup(STDOUT_FILENO);
	if (cmd->builtin != NONE && cmd_size(mini->cmd) == 1)
	{
		fd_handler(mini, cmd);
		exec_builtin(mini);
		return ;
	}
	else
		piper(mini, cmd, initial_fds);
	while (cmd)
	{
		waitpid(cmd->pid, &(sig->status), 0);
		sig->status = WEXITSTATUS(sig->status);
		close_fds(cmd->fd);
		cmd = cmd->next;
	}
	mini->cmd->fd[0] = STDIN_FILENO;
	mini->cmd->fd[1] = STDOUT_FILENO;
	dup2(initial_fds[0], STDIN_FILENO);
	dup2(initial_fds[1], STDOUT_FILENO);
	close_fds(initial_fds);
	sig->working = FALSE;
}
