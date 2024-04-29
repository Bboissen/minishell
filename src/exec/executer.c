/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/29 11:39:45 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_mini *mini, t_cmd *cmd, int *sig_pipefd)
{
	t_sig	*sig;

	sig = get_sig();
	close(cmd->fd[0]);
	if (!cmd->out)
		dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	close(sig_pipefd[0]);
	if (cmd->builtin == NONE)
		execve(cmd->args[0], cmd->args, env_to_tab(mini->h_env));
	else
	{
		exec_builtin(mini);
		if (cmd_size(mini->h_cmd) > 1)
			write(sig_pipefd[1], sig, sizeof(t_sig));
		close(sig_pipefd[0]);
		exit(sig->status);
	}
}

static pid_t	exec(t_mini *mini, t_cmd *cmd, int *sig_pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child(mini, cmd, sig_pipefd);
	else if (pid > 0)
	{
		close(cmd->fd[1]);
		if (cmd->fd[0] != -1)
			dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[0]);
		close(sig_pipefd[1]);
	}
	return (pid);
}
//everything
// <test cat | grep o | grep a >test3 | grep o >test2 | ls
static void	piper(t_mini *mini, t_cmd *cmd, int *sig_pipefd, int *initial_fds)
{
	t_cmd	*nxt;
	int		pipefd[2];

	pipe(sig_pipefd);
	while (cmd->next)
	{
		fd_handler(mini, cmd);
		pipe(pipefd);
		cmd->fd[0] = pipefd[0];
		if (cmd->fd[1] == -1)
			cmd->fd[1] = pipefd[1];
		dprintf(2, "pipefd = |%d|%d|\n", pipefd[0], pipefd[1]);
		dprintf(2, "cmd->fd[0] = %d cmd->fd[1] = %d\n\n\n", cmd->fd[0], cmd->fd[1]);
		nxt = cmd->next;
		cmd->pid = exec(mini, cmd, sig_pipefd);
		cmd = nxt;
		
	}
	cmd->fd[0] = pipefd[0];
	if (!cmd->out)
		dup2(initial_fds[1], STDOUT_FILENO);
	fd_handler(mini, cmd);
	dprintf(2, "cmd->fd[0] = %d cmd->fd[1] = %d\n", cmd->fd[0], cmd->fd[1]);
	cmd->pid = exec(mini, cmd, sig_pipefd);
}

void	cmd_exec(t_mini *mini)
{
	t_cmd	*cmd;
	t_sig	*sig;
	int		initial_fds[2];
	int		sig_pipefd[2];

	sig = get_sig();
	sig->working = TRUE;
	cmd = mini->h_cmd;
	initial_fds[0] = dup(STDIN_FILENO);
	initial_fds[1] = dup(STDOUT_FILENO);
	piper(mini, cmd, sig_pipefd, initial_fds);
	while (cmd)
	{
		waitpid(cmd->pid, &(sig->status), 0);
		sig->status = WEXITSTATUS(sig->status);
		if (cmd_size(mini->h_cmd) > 1)
			read(sig_pipefd[0], sig, sizeof(t_sig));
		close_fds(cmd->fd);
		cmd = cmd->next;
	}
	close_fds(sig_pipefd);
	mini->cmd->fd[0] = STDIN_FILENO;
	mini->cmd->fd[1] = STDOUT_FILENO;
	dup2(initial_fds[0], STDIN_FILENO);
	dup2(initial_fds[1], STDOUT_FILENO);
	close_fds(initial_fds);
	sig->working = FALSE;
}
