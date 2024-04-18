/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:59 by bboissen          #+#    #+#             */
/*   Updated: 2024/04/17 16:07:08 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_checker(char *str, char *cmd, char **path, int *err);

//builtin not working
//all cmd skip bug
//
void	cmd_skip(t_cmd **cmd, t_token **token)
{
	while ((*token) && (*token)->type != PIPE)
		(*token) = (*token)->next;
	free_cmd(cmd);
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

char	**add_args(t_cmd **cmd, char *str)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	while ((*cmd)->args && (*cmd)->args[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		new_cmd[j] = ft_strdup((*cmd)->args[j]);
		j++;
	}
	new_cmd[j] = ft_strdup(str);
	if (!new_cmd[j])
		return (NULL);
	new_cmd[j + 1] = NULL;
	if ((*cmd)->args)
		free((*cmd)->args);
	return (new_cmd);
}

t_builtin	check_blt(t_cmd **cmd, char *str, int *arg_flag)
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
	if ((*cmd)->builtin != NONE)
		*arg_flag = 1;
	return ((*cmd)->builtin);
}

static char	*path_checker(char *str, char	*cmd, char	**path, int *err)
{
	char	*buff;
	int		i;

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
		{
			free(buff);
			return (NULL);
		}
		*err = access(cmd, X_OK);
		if (*err == -1)
			free(cmd);
		free(buff);
	}
	if (*err == -1)
		return (NULL);
	return (cmd);
}

void	path_finder(t_mini *mini, t_cmd **cmd, char *str)
{
	t_env	*local_env;
	int		err;
	char	*args;
	char	**path;

	args = NULL;
	local_env = mini->h_env;
	while (local_env && ft_strcmp(local_env->name, "PATH"))
		local_env = local_env->next;
	path = ft_split(local_env->value, ':');
	if (path)
	{
		args = path_checker(str, args, path, &err);
		free_array(path);
	}
	if (path == NULL || ((*cmd) == NULL && err == 0))
		err = MALLOC;
	else if (err == -1)
		err = errno;
	else
	{
		(*cmd)->args = malloc(sizeof(char *) * 2);
		(*cmd)->args[0] = args;
		(*cmd)->args[1] = NULL;
	}
}

void	free_array(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}