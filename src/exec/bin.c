/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:12 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/12 11:48:16 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	mini->cmd->pid = fork();
	if (mini->cmd->pid == 0)
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
		waitpid(mini->cmd->pid, &ret, 0);
	if (mini->sig.sigint == 1 || mini->sig.sigquit == 1)
		return (mini->sig.status);
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	else
		ret = !!ret;
	return (ret);
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
