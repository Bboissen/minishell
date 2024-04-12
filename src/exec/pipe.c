/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/12 12:49:24 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Executes a command in a new process.
 * @param {t_mini*} mini - The main structure of the shell containing the command to be executed.
 * @return {pid_t} - Returns the process ID of the new process.
 */
pid_t	exec(t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(mini->cmd->fd[0]);
		dup2(mini->cmd->fd[1], 1);
		close(mini->cmd->fd[1]);
		execve(mini->cmd->args[0], mini->cmd->args, mini->env);
	}
	else if (pid > 0)
	{
		close(mini->cmd->fd[1]);
		dup2(mini->cmd->fd[0], 0);
		close(mini->cmd->fd[0]);
	}
	else
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

void	fd_handler(t_mini *mini)
{
	if (mini->cmd->in != 0)
	{
		mini->cmd->fd[0] = open(mini->cmd->in);
		if (mini->cmd->fd[0] == -1)
			return (error_manager(mini, errno));
	}
	else
		mini->cmd->fd[0] = 0;
	if (mini->cmd->out != 0)
		mini->cmd->fd[0] = open(mini->cmd->out);
	else
		mini->cmd->fd[1] = 1;
}

/**
 * Sets up and manages pipes for command execution.
 * @param {t_mini*} mini - The main structure of the shell containing the commands to be executed.
 * @return {void}
 */
void	pipex(t_mini *mini)
{
	int		i;
	int		size;
	t_cmd	*nxt;

	i = 0;
	size = ft_lstsize(mini->h_cmd);
	if (size == 1)
	{
		mini->cmd->pid = exec(mini);
		return ;
	}
	pipe(mini->cmd->fd);
	mini->cmd->pid = exec(mini);
	while (i++ < size - 2)
	{
		pipe(mini->cmd->fd);
		nxt = mini->cmd->next;
		nxt->pid = exec(mini);
		mini->cmd = nxt;
	}
	nxt = mini->cmd->next;
	pipe(nxt->fd);
	nxt->pid = exec(mini);
	return (clean_fd(mini));
}

/**
 * Handles file descriptors for input and output redirection, and executes the commands.
 * @param {t_mini*} mini - The main structure of the shell containing the commands to be executed and the file descriptors.
 * @return {int} - Returns the exit status of the last command executed.
 */
int	cmd_exec(t_mini *mini)
{
	mini->cmd = mini->h_cmd;
	mini->cmd->fd[0] = open(mini->cmd->in, O_RDONLY);
	if (mini->cmd->fd[0] < 0)
	{
		close(mini->cmd->fd[0]);
		mini->cmd->fd[0] = open("/dev/null", O_RDONLY);
	}
	mini->cmd->fd[1] = open(mini->cmd->out, O_WRONLY);
	if (mini->cmd->fd[1] < 0)
		mini->cmd->fd[1] = open("/dev/null", O_WRONLY);
	dup2(mini->cmd->fd[0], 0);
	close(mini->cmd->fd[0]);
	pipex(mini);
	while (mini->cmd)
	{
		waitpid(mini->cmd->pid, &(mini->sig.status), 0);
		clean_fd(mini);
		mini->cmd = mini->cmd->next;
	}
	mini->sig.status = WEXITSTATUS(mini->sig.status);
	return (mini->sig.status);
}
