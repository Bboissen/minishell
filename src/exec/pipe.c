/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/23 12:32:57 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	exec_builtin(char **args, t_mini *mini)
{
	t_sig	*sig;

	sig = get_sig();
	if (mini->cmd->builtin == CD)
		sig->status = mini_cd(mini);
	else if (mini->cmd->builtin == ECHO)
		sig->status = mini_echo(mini);
	else if (mini->cmd->builtin == ENV)
		sig->status = mini_env(mini);
	else if (mini->cmd->builtin == EXPORT)
		sig->status = mini_export(args, mini->env);
	else if (mini->cmd->builtin == PWD)
		sig->status = mini_pwd();
	else if (mini->cmd->builtin == UNSET)
		sig->status = mini_unset(mini);
	if (mini->cmd->builtin == EXIT)
		sig->status = mini_exit(mini);
}


static pid_t	exec(t_mini *mini, t_cmd *cmd, int *sigpipe_fd)
{
	pid_t	pid;
	t_sig	*sig;

	sig = get_sig();
	pid = fork();
	if (pid == 0)
	{
		dup2(cmd->fd[0], 0);
		dup2(cmd->fd[1], 1);
		close_fds(cmd->fd);
		if (cmd->builtin == NONE)
			execve(cmd->args[0], cmd->args, env_to_tab(mini->h_env));
		else
		{
			exec_builtin(cmd->args, mini);
			printf("exit sig sent: %d\n", sig->exit);
			write(sigpipe_fd[1], sig, sizeof(t_sig));
			exit(0);
		}
	}
	else if (pid > 0)
	{
		dup2(cmd->fd[0], 0);
		close_fds(cmd->fd);
	}
	return (pid);
}

static void	fd_handler(t_mini *mini, t_cmd *cmd)
{
	(void)mini;
	if (cmd->in != NULL)
		cmd->fd[0] = open(cmd->in, O_RDONLY);
	if (cmd->out != NULL)
		cmd->fd[1] = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}


static void	piper(t_mini *mini, t_cmd *cmd, int *sigpipe_fd)
{
	t_cmd	*nxt;
	int		pipefd[2];

	while (cmd)
	{
		fd_handler(mini, cmd);
		if (!cmd->out && cmd->next && !cmd->next->in)
		{
			pipe(pipefd);
			if (!cmd->in)
				cmd->fd[0] = pipefd[0];
			else
			{
				close(pipefd[0]);
				cmd->fd[0] = -1;
			}
			if (!cmd->out)
				cmd->fd[1] = pipefd[1];
		}
		nxt = cmd->next;
		cmd->pid = exec(mini, cmd, sigpipe_fd);
		cmd = nxt;
	}
}


int	cmd_exec(t_mini *mini)
{
	t_cmd	*cmd;
	t_sig	*sig;
	int		initial_fds[2];
	int		sigpipe_fd[2];

	sig = get_sig();
	sig->working = TRUE;
	cmd = mini->h_cmd;
	initial_fds[0] = dup(STDIN_FILENO);
	initial_fds[1] = dup(STDOUT_FILENO);
	piper(mini, cmd, sigpipe_fd);
	while (cmd)
	{
		waitpid(cmd->pid, &(sig->status), 0);
		sig->status = WEXITSTATUS(sig->status);
		read(sigpipe_fd[0], sig, sizeof(t_sig));
		printf("exit sig received: %d\n", sig->exit);
		close_fds(cmd->fd);
		cmd = cmd->next;
	}
	mini->cmd->fd[0] = STDIN_FILENO;
	mini->cmd->fd[1] = STDOUT_FILENO;
	dup2(initial_fds[0], STDIN_FILENO);
	dup2(initial_fds[1], STDOUT_FILENO);
	close_fds(initial_fds);
	sig->working = FALSE;
	return (sig->status);
}
