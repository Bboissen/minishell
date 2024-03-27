/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:12 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 17:01:13 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints an error message based on the accessibility of the given path.
 * @param {char*} path - The path to check.
 * @return {int} - Returns CMD if the file does not exist or is not a command, DIRECTORY if the file is not executable.
 */
static int	error_message(char *path)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);

	if (access(path, F_OK) != 0)
		return (ft_putendl_fd(": No such file or directory", STDERR),
			CMD);
	else if (access(path, X_OK) != 0)
		return (ft_putendl_fd(": Permission denied", STDERR), DIRECTORY);
	else
		return (ft_putendl_fd(": command not found", STDERR), CMD);
}

/**
 * Executes a command with the given arguments and environment.
 * @param {char*} path - The path to the command.
 * @param {char**} args - The arguments for the command.
 * @param {t_env*} env - The environment for the command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns the status of the command execution.
 */
static int	cmd_execution(char *path, char **args, t_env *env, t_mini *mini)
{
	char	**env_array;
	int		ret;

	ret = SUCCESS;
	mini->sig.pid = fork();
	if (mini->sig.pid == 0)
	{
		env_array = ft_split(env_to_str(env), '\n');
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		free_tab(env_array);
		free_token(mini->token);
		exit(ret);
	}
	else
		waitpid(mini->sig.pid, &ret, 0);
	if (mini->sig.sigint == 1 || mini->sig.sigquit == 1)
		return (mini->sig.status);
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	else
		ret = !!ret;
	return (ret);
}

/**
 * Joins two strings with a "/" separator.
 * @param {char*} s1 - The first string.
 * @param {char*} s2 - The second string.
 * @return {char*} - Returns a new string that is the result of the join.
 */
static char	*path_join(char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

/**
 * Checks if a command exists in a directory.
 * @param {char*} bin - The directory to check.
 * @param {char*} command - The command to check for.
 * @return {char*} - Returns the path to the command if it exists, NULL otherwise.
 */
static char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, command) == 0)
		{
			path = path_join(bin, item->d_name);
			break ;
		}
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

/**
 * Executes a binary command with the given arguments and environment.
 * @param {char**} args - The arguments for the command.
 * @param {t_env*} env - The environment for the command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns the status of the command execution.
 */
int	exec_bin(char **args, t_env *env, t_mini *mini)
{
	int		i;
	int		status;
	t_env	*path_env;
	char	**bin;
	char	*path;

	path_env = env;
	while (env && env->name && ft_strncmp(env->name, "PATH", 4) != 0)
		env = env->next;
	if (!path_env)
		return (cmd_execution(args[0], args, env, mini));
	bin = ft_split(path_env->value, ':');
	if (!args[0] || !bin[0])
		return (ERROR);
	path = NULL;
	i = -1;
	while (bin[++i] && !path)
		path = check_dir(bin[i], args[0]);
	free_tab(bin);
	if (path)
		status = cmd_execution(path, args, env, mini);
	else
		status = cmd_execution(args[0], args, env, mini);
	return (ft_memdel(path), status);
}
