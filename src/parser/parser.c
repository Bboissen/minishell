/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:07 by bbsn              #+#    #+#             */
/*   Updated: 2024/05/06 17:14:46 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd(t_mini *mini, t_cmd **cmd, int skip);
static void	cmd_setter(t_mini **mini, t_cmd **cmd, int skip, int *arg_flag);

/**
 * @brief Parses the tokens in the shell.
 * 
 * @param mini The main structure of the shell.
 * @return {int} - Returns the status of the paring.
 * 
 */
int	parser(t_mini *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		arg_flag;
	int		skip;

	arg_flag = 0;
	token = mini->h_token;
	init_cmd(mini, &cmd, 0);
	get_sig()->status = 0;
	while (token)
	{
		skip = 0;
		if (token && is_file(token->type))
			skip += check_file(mini, &cmd, &token);
		if (token && token->type == STR)
			skip += check_cmd(mini, &cmd, &token, &arg_flag);
		if (token && token->type == PIPE)
		{
			cmd_setter(&mini, &cmd, skip, &arg_flag);
			token = token->next;
		}
	}
	if (cmd)
		new_cmd(&mini, &cmd, &arg_flag);
	return (get_sig()->status);
}

/**
 * @brief Initializes a command structure.
 * 
 * @param mini The main structure of the shell.
 * @param cmd Pointer to the command structure to be initialized.
 * @param skip Determines if the input of the command
 * should be set to "/dev/null".
 * @return {int} - Returns SUCCESS if the command is successfully initialized,
 * otherwise returns the result of error_manager.
 */
static int	init_cmd(t_mini *mini, t_cmd **cmd, int skip)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (error_manager(mini, MALLOC, NULL, NULL));
	(*cmd)->args = NULL;
	if (skip == 0)
		(*cmd)->in = NULL;
	else
	{
		(*cmd)->in = ft_strdup("/dev/null");
		if (!(*cmd)->in)
			return (free((*cmd)), error_manager(mini, MALLOC, NULL, NULL));
	}
	(*cmd)->out = NULL;
	(*cmd)->fd[0] = -1;
	(*cmd)->fd[1] = -1;
	(*cmd)->pid = -1;
	(*cmd)->append = 0;
	(*cmd)->builtin = NONE;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
	return (SUCCESS);
}

/**
 * @brief Sets a command in the shell.
 * 
 * @param mini Pointer to the main structure of the shell.
 * @param cmd Pointer to the command to be set.
 * @param skip Determines if the input of the command
 * should be set to "/dev/null".
 * @param arg_flag Pointer to the argument flag.
 */
static void	cmd_setter(t_mini **mini, t_cmd **cmd, int skip, int *arg_flag)
{
	if (*cmd)
		new_cmd(mini, cmd, arg_flag);
	init_cmd((*mini), cmd, skip);
	get_sig()->status = SUCCESS;
	*arg_flag = 0;
}
