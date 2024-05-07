/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 13:25:29 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		waitfor_commands(t_mini *mini, t_sig *sig);
static void		piper(t_mini *mini, t_cmd *cmd);
static pid_t	exec(t_mini *mini, t_cmd *cmd);
static void		exec_child(t_mini *mini, t_cmd *cmd);

/**
 * @brief Executes the commands.
 * 
 * @param mini Pointer to the mini shell structure.
 */
void	cmd_exec(t_mini *mini)
{
	t_sig	*sig;

	sig = get_sig();
	sig->working = TRUE;
	mini->cmd = mini->h_cmd;
	mini->initial_fds[0] = dup(STDIN_FILENO);
	mini->initial_fds[1] = dup(STDOUT_FILENO);
	if (mini->cmd->builtin != NONE && cmd_size(mini->cmd) == 1)
	{
		fd_handler(mini, mini->cmd);
		exec_builtin(mini, mini->cmd);
	}
	else
		piper(mini, mini->cmd);
	waitfor_commands(mini, sig);
	sig->working = FALSE;
}

/**
 * @brief Waits for the commands to finish execution.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param sig Pointer to the signal structure.
 * @param initial_fds Array of initial file descriptors.
 */
static void	waitfor_commands(t_mini *mini, t_sig *sig)
{
	int	status;

	status = SUCCESS;
	while (mini->cmd)
	{
		waitpid(mini->cmd->pid, &(status), 0);
		if (WIFSIGNALED(status))
			sig->status = 128 + WTERMSIG(status);
		else if (mini->cmd->builtin == NONE || cmd_size(mini->h_cmd) != 1)
			sig->status = WEXITSTATUS(status);
		close_fds(mini->cmd->fd);
		mini->cmd = mini->cmd->next;
	}
	dup2(mini->initial_fds[0], STDIN_FILENO);
	dup2(mini->initial_fds[1], STDOUT_FILENO);
	close_fds(mini->initial_fds);
}

/**
 * @brief Handles the piping of commands.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @param initial_fds Array of initial file descriptors.
 */
static void	piper(t_mini *mini, t_cmd *cmd)
{
	int		pipefd[2];

	while (cmd->next)
	{
		fd_handler(mini, cmd);
		if (pipe(pipefd) == -1)
			error_manager(mini, errno, "pipe", NULL);
		cmd->fd[0] = pipefd[0];
		cmd->fd[1] = pipefd[1];
		cmd->pid = exec(mini, cmd);
		cmd = cmd->next;
	}
	fd_handler(mini, cmd);
	cmd->fd[0] = mini->initial_fds[0];
	if (!cmd->out)
		dup2(mini->initial_fds[1], STDOUT_FILENO);
	cmd->pid = exec(mini, cmd);
}

/**
 * @brief Executes a command.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @param initial_fds Array of initial file descriptors.
 * @return {pid_t} - Returns the process ID of the executed command.
 */
static pid_t	exec(t_mini *mini, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child(mini, cmd);
	else if (pid > 0)
	{
		if (cmd->fd[0] != -1)
			dup2(cmd->fd[0], STDIN_FILENO);
		close_fds(cmd->fd);
	}
	else
		error_manager(mini, errno, "fork", NULL);
	return (pid);
}

/**
 * @brief Executes the child process.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @param initial_fds Array of initial file descriptors.
 */
static void	exec_child(t_mini *mini, t_cmd *cmd)
{
	if (!cmd->out)
		dup2(cmd->fd[1], STDOUT_FILENO);
	close_fds(cmd->fd);
	close_fds(mini->initial_fds);
	if ((cmd->builtin == NONE && cmd->args))
		execve(cmd->args[0], cmd->args, env_to_tab(mini));
	else
	{
		exec_builtin(mini, cmd);
		clean_exit(mini);
	}
}
