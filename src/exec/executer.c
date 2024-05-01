/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/01 15:48:13 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child(t_mini *mini, t_cmd *cmd, int *sig_pipefd, int *initial_fds)
{
	t_sig	*sig;

	sig = get_sig();
	if (!cmd->out)
		dup2(cmd->fd[1], STDOUT_FILENO);
	close_fds(cmd->fd);
	close_fds(initial_fds);
	if (cmd->builtin == NONE)
	{
		execve(cmd->args[0], cmd->args, env_to_tab(mini));
	}
	else
	{
		sig->status = exec_builtin(mini, cmd);
		if (cmd_size(mini->h_cmd) > 1)
			write(sig_pipefd[1], sig, sizeof(t_sig));
		close(sig_pipefd[0]);
	}
	exit(sig->status);
}

static pid_t	exec(t_mini *mini, t_cmd *cmd, int *sig_pipefd, int *initial_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		get_sig()->status = exec_child(mini, cmd, sig_pipefd, initial_fds);
	else if (pid > 0)
	{
		if (cmd->fd[0] != -1)
			dup2(cmd->fd[0], STDIN_FILENO);
		close_fds(cmd->fd);
		close(sig_pipefd[1]);
	}
	return (pid);
}

static void	piper(t_mini *mini, t_cmd *cmd, int *sig_pipefd, int *initial_fds)
{
	int		pipefd[2];

	pipe(sig_pipefd);
	while (cmd->next)
	{
		fd_handler(mini, cmd);
		pipe(pipefd);
		cmd->fd[0] = pipefd[0];
		cmd->fd[1] = pipefd[1];
		cmd->pid = exec(mini, cmd, sig_pipefd, initial_fds);
		cmd = cmd->next;
	}
	fd_handler(mini, cmd);
	cmd->fd[0] = initial_fds[0];
	if (!cmd->out)
		dup2(initial_fds[1], STDOUT_FILENO);
	cmd->pid = exec(mini, cmd, sig_pipefd, initial_fds);
}

void	cmd_exec(t_mini *mini)
{
	t_sig	*sig;
	int		status;
	int		initial_fds[2];
	int		sig_pipefd[2];

	sig = get_sig();
	sig->working = TRUE;
	mini->cmd = mini->h_cmd;
	initial_fds[0] = dup(STDIN_FILENO);
	initial_fds[1] = dup(STDOUT_FILENO);
	if (mini->cmd->builtin != NONE && cmd_size(mini->cmd) == 1)
	{
		fd_handler(mini, mini->cmd);
		exec_builtin(mini, mini->cmd);
	}
	else
		piper(mini, mini->cmd, sig_pipefd, initial_fds);
	while (mini->cmd)
	{
		waitpid(mini->cmd->pid, &(status), 0);
		if (WIFEXITED(status))
			sig->status = WEXITSTATUS(status);
		if (cmd_size(mini->h_cmd) > 1)
			read(sig_pipefd[0], sig, sizeof(t_sig));
		close_fds(mini->cmd->fd);
		mini->cmd = mini->cmd->next;
	}
	dup2(initial_fds[0], STDIN_FILENO);
	dup2(initial_fds[1], STDOUT_FILENO);
	close_fds(initial_fds);
	sig->working = FALSE;
}
