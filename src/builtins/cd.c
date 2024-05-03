/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:24:55 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 16:07:21 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds the home path to the given path if it starts with '~/'.
 *
 * @param mini The main structure of the minishell.
 * @param path The path to which the home path should be added.
 * @return The new path with the home path added, or the original 
 * path if it didn't start with '~/'. 
 */
static char	*add_home_path(t_mini *mini, char *path)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (path && path[0] == '~' && (path[1] && path[1] == '/'))
	{
		tmp1 = get_env_value(mini, "HOME");
		if (tmp1)
		{
			tmp2 = ft_substr(path, 1, ft_strlen(path));
			if (!tmp2)
				return (error_manager(mini, MALLOC, NULL, NULL), NULL);
			ft_memdel(path);
			path = ft_strjoin(tmp1, tmp2);
			if (!path)
				return (error_manager(mini, MALLOC, NULL, NULL), NULL);
		}
	}
	ft_memdel(tmp2);
	return (path);
}

/**
 * @brief Changes the current directory to the given path and 
 * updates the PWD and OLDPWD environment variables.
 *
 * @param mini The main structure of the minishell.
 * @param path The path to change to.
 * @return {int} SUCCESS if the directory was changed successfully,
 * ERROR otherwise.
 */
static int	change(t_mini *mini, char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_strdup(get_env_value(mini, "PWD"));
	if (chdir(path) == 0)
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			set_env(&mini->h_env, "PWD", new_pwd);
			ft_memdel(new_pwd);
		}
		if (old_pwd)
		{
			set_env(&mini->h_env, "OLDPWD", old_pwd);
			ft_memdel(old_pwd);
		}
		return (SUCCESS);
	}
	else
		ft_memdel(old_pwd);
	return (cd_err(mini, DIRECTORY, path), ERROR);
}

/**
 * @brief Changes the current directory to the previous one
 * stored in the OLDPWD environment variable.
 *
 * @param mini The main structure of the minishell.
 * @return {int} ERROR if the command was '-',
 * SUCCESS otherwise.
 */
static int	backward_dir(t_mini *mini, t_cmd *cmd)
{
	char	*tmp;
	char	**args;

	args = cmd->args;
	if (ft_strequ(args[0], "-"))
	{
		tmp = get_env_value(mini, "OLDPWD");
		if (tmp)
			change(mini, tmp);
		tmp = get_env_value(mini, "PWD");
		if (tmp)
			ft_printfd(1, "%s\n", tmp);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Changes the current directory to the one specified in the arguments,
 * or to the home directory if no arguments are given.
 *
 * @param mini The main structure of the minishell.
 * @return {int} SUCCESS if the directory was changed successfully,
 * ERROR otherwise.
 */
int	mini_cd(t_mini *mini, t_cmd *cmd)
{
	char	*home;
	char	**args;

	home = NULL;
	args = cmd->args;
	if (arg_exists(args, 1) && !ft_strequ(args[0], "--"))
		return (cd_err(mini, ERROR, NULL), ERROR);
	else if (arg_exists(args, 1) && ft_strequ(args[0], "--"))
		args++;
	if (args && args[0] && args[0][0] == '\0')
		return (SUCCESS);
	if (!args || (ft_strequ(args[0], "~") && !args[1]))
	{
		if (!get_env_value(mini, "HOME"))
			return (cd_err(mini, MISSING, NULL), ERROR);
		home = ft_strdup(get_env_value(mini, "HOME"));
		if (!home)
			return (error_manager(mini, MALLOC, NULL, NULL), ERROR);
		return (change(mini, home), free(home), SUCCESS);
	}
	if (args && args[0][0] == '-' && !args[0][1])
		return (backward_dir(mini, cmd), SUCCESS);
	if (access(args[0], F_OK) == -1)
		args[0] = add_home_path(mini, args[0]);
	return (change(mini, args[0]));
}
