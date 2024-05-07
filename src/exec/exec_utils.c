/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:54:08 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 09:40:59 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the built-in commands in a mini shell.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @return {int} - Returns the status of the command execution.
 */
int	exec_builtin(t_mini *mini, t_cmd *cmd)
{
	t_sig	*sig;

	sig = get_sig();
	if (cmd->builtin == CD)
		sig->status = mini_cd(mini, cmd);
	if (cmd->builtin == ECHO)
		sig->status = mini_echo(mini, cmd);
	else if (cmd->builtin == ENV)
		sig->status = mini_env(mini, cmd);
	else if (cmd->builtin == EXPORT)
		sig->status = mini_export(mini, cmd);
	else if (cmd->builtin == PWD)
		sig->status = mini_pwd(mini, cmd);
	else if (cmd->builtin == UNSET)
		sig->status = mini_unset(mini, cmd);
	else if (cmd->builtin == EXIT)
		sig->status = mini_exit(mini, cmd);
	return (sig->status);
}

/**
 * @brief Check if an argument exists at a given index.
 * 
 * @param args The array of arguments.
 * @param index The index to check.
 * @return {int} - TRUE if an argument exists at the given index,
 * FALSE otherwise.
 */
int	arg_exists(char **args, int index)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (FALSE);
	while (args[i] != NULL)
		i++;
	return (i > index);
}

/**
 * @brief Calculate the size of the command.
 * 
 * @param h_cmd The head of the command list.
 * @return {int} - The size of the command list.
 */
int	cmd_size(t_cmd *h_cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = h_cmd;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/**
 * @brief Handles file descriptors for input and output redirection.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 */
void	fd_handler(t_mini *mini, t_cmd *cmd)
{
	int	in;
	int	out;

	(void)mini;
	if (cmd->in != NULL)
	{
		in = open(cmd->in, O_RDONLY);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->out != NULL)
	{
		out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
