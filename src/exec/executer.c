/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 12:21:38 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		wait_commands(t_mini *mini);
static void		piper(t_mini *mini, t_cmd *cmd, int *initial_fds);
static pid_t	exec(t_mini *mini, t_cmd *cmd, int *initial_fds);
static void		exec_child(t_mini *mini, t_cmd *cmd, int *initial_fds);

/**
 * @brief Executes the command in a mini shell.
 * 
 * @param mini Pointer to the minishell structure.
 */
void	cmd_exec(t_mini *mini)
{
	int		status;
	int		initial_fds[2];

	status = 0;
	get_sig()->working = TRUE;
	mini->cmd = mini->h_cmd;
	initial_fds[0] = dup(STDIN_FILENO);
	initial_fds[1] = dup(STDOUT_FILENO);
	if (mini->cmd->builtin != NONE && cmd_size(mini->cmd) == 1)
	{
		fd_handler(mini, mini->cmd);
		exec_builtin(mini, mini->cmd);
	}
	else
		piper(mini, mini->cmd, initial_fds);
	while (mini->cmd)
		wait_commands(mini);
	dup2(initial_fds[0], STDIN_FILENO);
	dup2(initial_fds[1], STDOUT_FILENO);
	close_fds(initial_fds);
	get_sig()->working = FALSE;
}

/**
 * @brief Executes a command in pipes.
 * 
 * @param mini Pointer to the minishell structure.
 * @param cmd Pointer to the command structure.
 * @param initial_fds Array of initial file descriptors.
 * @return {pid_t} - Returns the process ID of the executed command.
 */
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
	if (!cmd->out)
		dup2(initial_fds[1], STDOUT_FILENO);
	cmd->pid = exec(mini, cmd, initial_fds);
}

/**
 * @brief Processes the commands in a loop.
 * 
 * @param mini Pointer to the minishell structure.
 */
static void	wait_commands(t_mini *mini)
{
	int	status;

	while (mini->cmd)
	{
		waitpid(mini->cmd->pid, &(status), 0);
		if (WIFSIGNALED(status))
			get_sig()->status = 128 + WTERMSIG(status);
		else if (mini->cmd->builtin == NONE || cmd_size(mini->h_cmd) != 1)
			get_sig()->status = WEXITSTATUS(status);
		close_fds(mini->cmd->fd);
		mini->cmd = mini->cmd->next;
	}
}

/**
 * @brief Runs the child and parent actions.
 * 
 * @param mini Pointer to the minishell structure.
 * @param cmd Pointer to the command structure.
 * @param initial_fds Array of initial file descriptors.
 */
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

/**
 * @brief Execve or builtin and exit in a child process.
 * 
 * @param mini Pointer to the minishell structure.
 * @param cmd Pointer to the command structure.
 * @param initial_fds Array of initial file descriptors.
 */
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
		exec_builtin(mini, cmd);
		clean_exit(mini);
	}
}
