/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/22 17:03:06 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Execute a built-in command.
 * 
 * @param {char**} args - The arguments for the command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns the result of the command execution.
 */
static void	exec_builtin(char **args, t_mini *mini)
{
	t_sig	*sig;

	sig = get_sig();
	(void)args;
	/*if (mini->cmd->builtin == CD)
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
		sig->status = mini_unset(mini);*/
	if (mini->cmd->builtin == EXIT)
		sig->status = mini_exit(mini);
}

/**
 * Executes a command in a new process.
 * 
 * @param {t_mini*} mini - The main structure of the 
 * shell containing the command to be executed.
 * @return {pid_t} - Returns the process ID of the new process.
 */
static pid_t	exec(t_mini *mini, t_cmd *cmd)
{
	pid_t	pid;

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
	{
		cmd->fd[0] = open(cmd->in, O_RDONLY);
		printf("cmd->in: %d\n", cmd->fd[0]);
		//if (cmd->fd[0] == -1)
			//return (error_manager(mini, FD));
	}
	if (cmd->out != NULL)
	{
		cmd->fd[1] = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//if (cmd->fd[1] == -1)
			//return (error_manager(mini, FD));
	}
}

/**
 * Sets up and manages pipes for command execution.
 * 
 * @param {t_mini*} mini - The main structure of the 
 * shell containing the commands to be executed.
 * @return {void}
 */
static void	pipex(t_mini *mini, t_cmd *cmd)
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
		cmd->pid = exec(mini, cmd);
		cmd = nxt;
	}
}

/**
 * Handles file descriptors for input and output redirection, 
 * and executes the commands.
 * 
 * @param {t_mini*} mini - The main structure of the shell containing 
 * the commands to be executed and the file descriptors.
 * @return {int} - Returns the exit status of the last command executed.
 */
int	cmd_exec(t_mini *mini)
{
	t_cmd	*cmd;
	t_sig	*sig;
	int		initial_fds[2];

	sig = get_sig();
	sig->working = TRUE;
	cmd = mini->h_cmd;
	initial_fds[0] = dup(STDIN_FILENO);
	initial_fds[1] = dup(STDOUT_FILENO);
	pipex(mini, cmd);
	while (cmd)
	{
		waitpid(cmd->pid, &(sig->status), 0);
		close_fds(cmd->fd);
		cmd = cmd->next;
	}
	mini->cmd->fd[0] = STDIN_FILENO;
	mini->cmd->fd[1] = STDOUT_FILENO;
	sig->status = WEXITSTATUS(sig->status);
	sig->working = FALSE;
	dup2(initial_fds[0], STDIN_FILENO);
	dup2(initial_fds[1], STDOUT_FILENO);
	close_fds(initial_fds);
	return (sig->status);
}
