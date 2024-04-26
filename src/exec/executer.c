/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/26 16:55:26 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_mini *mini, t_cmd *cmd, int *sig_pipefd)
{
	t_sig	*sig;

	sig = get_sig();
	close(sig_pipefd[0]);
	close(cmd->fd[0]);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[1]);
	if (cmd->builtin == NONE)
		execve(cmd->args[0], cmd->args, env_to_tab(mini->h_env));
	else
	{
		exec_builtin(mini);
		if (cmd_size(mini->h_cmd) > 1)
			write(sig_pipefd[1], sig, sizeof(t_sig));
		exit(sig->status);
	}
}

static pid_t	exec(t_mini *mini, t_cmd *cmd, int *sig_pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child(mini, cmd, sig_pipefd);
	else
	{
		close(cmd->fd[1]);
		close(sig_pipefd[1]);
		if (cmd->next != NULL)
			dup2(cmd->fd[0], 0);
	}
	return (pid);
}

static void	piper(t_mini *mini, t_cmd *cmd, int *sig_pipefd)
{
	int		pipefd[2];

	while (cmd)
	{
		fd_handler(cmd);
		if (cmd->next)
		{
			pipe(pipefd);
			printf("pipefd[0]: %d pipefd[1]: %d\n", pipefd[0], pipefd[1]);
			cmd->fd[1] = pipefd[1];
			cmd->next->fd[0] = pipefd[0];
		}
		cmd->pid = exec(mini, cmd, sig_pipefd);
		cmd = cmd->next;
	}
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
	if (cmd_size(mini->h_cmd) == 1 && cmd->builtin != NONE)
		return (exec_builtin(mini));
	pipe(sig_pipefd);
	piper(mini, cmd, sig_pipefd);
	while (cmd)
	{
		waitpid(cmd->pid, &(sig->status), 0);
		sig->status = WEXITSTATUS(sig->status);
		if (cmd_size(mini->h_cmd) > 1)
			read(sig_pipefd[0], sig, sizeof(t_sig));
		cmd = cmd->next;
	}
	dup2(initial_fds[0], STDIN_FILENO);
	dup2(initial_fds[1], STDOUT_FILENO);
	close_fds(sig_pipefd);
	close_fds(initial_fds);
	sig->working = FALSE;
}
