/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:59 by bboissen          #+#    #+#             */
/*   Updated: 2024/05/04 15:42:41 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_skip(t_mini *mini, t_cmd **cmd, t_token **token, int err)
{
	if (err == INPUT || err == HEREDOC
		|| err == APPEND || err == TRUNC)
		parser_err(mini, (*token)->next->str, errno);
	else
		parser_err(mini, (*token)->str, err);
	while ((*token) && (*token)->type != PIPE)
		(*token) = (*token)->next;
	free_cmd(cmd);
	if (mini->cmd)
	{
		if (mini->cmd->out)
			free(mini->cmd->out);
		mini->cmd->out = ft_strdup("/dev/null");
		if (mini->cmd->out == NULL)
			error_manager(mini, MALLOC, NULL, NULL);
	}
}

void	new_cmd(t_mini **mini, t_cmd **cmd, int *arg_flag)
{
	if (!(*mini)->cmd)
	{
		(*mini)->h_cmd = *cmd;
		(*mini)->cmd = (*mini)->h_cmd;
	}
	else
	{
		(*mini)->cmd->next = *cmd;
		(*cmd)->prev = (*mini)->cmd;
		(*mini)->cmd = (*mini)->cmd->next;
	}
	*arg_flag = 0;
}

static void	args_cleaner( t_mini *mini, t_cmd **cmd, char **new_cmd)
{
	free_tab(new_cmd);
	free_cmd(cmd);
	error_manager(mini, MALLOC, NULL, NULL);
}

char	**add_args(t_mini *mini, t_cmd **cmd, char *str)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	while ((*cmd)->args && (*cmd)->args[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	if (!new_cmd)
		return (free_cmd(cmd), error_manager(mini, MALLOC, NULL, NULL), NULL);
	j = 0;
	while (j < i)
	{
		new_cmd[j] = ft_strdup((*cmd)->args[j]);
		if (!new_cmd[j])
			args_cleaner(mini, cmd, new_cmd);
		j++;
	}
	new_cmd[j] = ft_strdup(str);
	if (!new_cmd[j])
		args_cleaner(mini, cmd, new_cmd);
	new_cmd[j + 1] = NULL;
	if ((*cmd)->args)
		free_tab((*cmd)->args);
	return (new_cmd);
}

char	*path_checker(char *str, char *cmd, char **path, int *err)
{
	char		*buff;
	int			i;
	struct stat	st;

	i = -1;
	*err = -1;
	while (path[++i] && *err == -1)
	{
		*err = 0;
		buff = ft_strjoin(path[i], "/");
		if (buff == NULL)
			return (NULL);
		cmd = ft_strjoin(buff, str);
		if (cmd == NULL)
			return (free(buff), NULL);
		*err = stat(cmd, &st);
		if (*err == -1)
			free(cmd);
		free(buff);
	}
	if (*err == -1)
		return (NULL);
	return (cmd);
}
