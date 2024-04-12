/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:59 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/12 16:28:00 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_skip(t_mini *mini, t_cmd **cmd, t_token *token)
{
	mini->sig.status = errno;
	printf_fd(2, "%s: %s: %s\n", mini->name,
		strerror(errno), token->next->str);
	free_cmd(*cmd);
	while (token && token->type != PIPE)
		token = token->next;
}

void	new_cmd(t_mini *mini, t_cmd **cmd, int *arg_flag)
{
	if (!mini->cmd)
	{
		mini->cmd_h = *cmd;
		mini->cmd = mini->cmd_h;
	}
	else
	{
		mini->cmd->next = *cmd;
		(*cmd)->prev = mini->cmd;
		mini->cmd = mini->cmd->next;
	}
	*arg_flag = 0;
}

char	**add_args(t_cmd **cmd, char *str)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	while ((*cmd)->args[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j <= i)
	{
		new_cmd[j] = ft_strdup((*cmd)->args[j]);
		if (!new_cmd[j++])
			return (NULL);
	}
	new_cmd[j] = ft_strdup(str);
	if (!new_cmd[j])
		return (NULL);
	new_cmd[j + 1] = NULL;
	free((*cmd)->args);
	return (new_cmd);
}

void	check_blt(t_mini *mini, t_cmd **cmd, char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		(*cmd)->builtin = ECHO;
	else if (ft_strcmp(str, "cd") == 0)
		(*cmd)->builtin = CD;
	else if (ft_strcmp(str, "pwd") == 0)
		(*cmd)->builtin = PWD;
	else if (ft_strcmp(str, "export") == 0)
		(*cmd)->builtin = EXPORT;
	else if (ft_strcmp(str, "unset") == 0)
		(*cmd)->builtin = UNSET;
	else if (ft_strcmp(str, "env") == 0)
		(*cmd)->builtin = ENV;
	else if (ft_strcmp(str, "exit") == 0)
		(*cmd)->builtin = EXIT;
	else
		(*cmd)->builtin = NONE;
}

void	path_finder(t_mini *mini, t_cmd *cmd, char *str)
{
	t_env	*local_env;
	int		err;
	char	*cmd;
	char	**path;

	cmd = NULL;
	local_env = mini->h_env;
	while (local_env && !ft_strcmp(local_env->name, "PATH"))
		local_env = local_env->next;
	path = ft_split(str + 5, ':');
	if (path)
	{
		err = path_checker(str, &cmd, path);
		free_array(path);
	}
	if (path == NULL || (cmd == NULL && err == 0))
		mini->sig.status = MALLOC;
	else if (err == -1)
		mini->sig.status = errno;
	else
	{
		cmd->args = malloc(sizeof(char *) * 2);
		cmd->args[0] = cmd;
		cmd->args[1] = NULL;
	}
}

static char	*path_checker(char const *str, char	**cmd, char	**path)
{
	char	*buff;
	int		i;
	int		err;

	i = -1;
	err = -1;
	while (path[++i] && err == -1)
	{
		// err = 0;
		buff = ft_strjoin(path[i], "/");
		if (buff == NULL)
			return (NULL);
		str = ft_strjoin(buff, str);
		if (str == NULL)
		{
			free(buff);
			return (NULL);
		}
		err = access(str, X_OK);
		if (err == -1)
			free(str);
		free(buff);
	}
	if (err != -1)
		*cmd = str;
	return (err);
}
