/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:24:55 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 13:15:04 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Add the home path to the given path if it starts with '~/'
 * @param {char*} path - The path to add the home path to.
 * @return {char*} - Returns the new path with the home path added.
 */
static char	*add_home_path(t_mini *mini, char *path)
{
	char	*tmp1;
	char	*tmp2;

	if (!ft_strncmp(path, "~/", 2))
	{
		tmp1 = get_env(mini->h_env, "HOME");
		if (tmp1)
		{
			tmp2 = ft_substr(path, 1, ft_strlen(path));
			free(path);
			path = ft_strjoin(tmp1, tmp2);
			return (free(tmp1), free(tmp2), path);
		}
	}
	return (path);
}

/**
 * Change the current directory to the given path and update the PWD and OLDPWD 
 * environment variables.
 * @param {char*} path - The path to change to.
 * @param {int} home - Flag to indicate if the path is the home directory.
 * @return {int} - Returns ERROR if the directory change was successful, 
 * SUCCESS otherwise.
 */
static int	change(t_mini *mini, char *path, int home)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env(&mini->h_env, "OLDPWD", pwd);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env(&mini->h_env, "PWD", pwd);
			free(pwd);
		}
		if (home)
			free(path);
		return (ERROR);
	}
	return (free(pwd), SUCCESS);
}

/**
 * Set the current directory to the given path and print an error message 
 * if the directory change was not successful.
 * @param {t_mini*} mini - The main structure of the shell.
 * @param {char*} path - The path to set as the current directory.
 * @param {int} home - Flag to indicate if the path is the home directory.
 * @return {int} - Returns SUCCESS if the directory was set successfully, 
 * ERROR otherwise.
 */
static int	set_directory(t_mini *mini, char *path, int home)
{
	struct stat	st;

	if (change(mini, path, home))
		return (ERROR);
	ft_printfd(2, "minishell: cd: %s", path);
	mini->sig.status = ERROR;
	if (stat(path, &st) == -1)
	{
		ft_printfd(2, ": No such file or directory");
		mini->sig.status = DIRECTORY;
	}
	else if (!(st.st_mode & S_IXUSR))
	{
		ft_printfd(2, ": Permission denied");
		mini->sig.status = CMD;
	}
	else
		ft_printfd(2, ": Not a directory");
	ft_printfd(2, "\n");
	if (home)
		free(path);
	return (SUCCESS);
}

/**
 * Change the current directory to the given path or to the previous directory 
 * if the path is '-'.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns ERROR if the directory change was successful, the 
 * result of set_directory otherwise.
 */
static int	s_path(t_mini *mini)
{
	char	*tmp;
	char	**args;

	args = mini->cmd->args;
	if (ft_strequ(args[1], "-"))
	{
		tmp = get_env(mini->h_env, "OLDPWD");
		if (tmp)
		{
			set_directory(mini, tmp, 0);
			free(tmp);
		}
		tmp = get_env(mini->h_env, "PWD");
		if (tmp)
		{
			ft_printfd(1, "%s\n", tmp);
			free(tmp);
		}
		return (ERROR);
	}
	return (set_directory(mini, args[1], 0));
}

/**
 * Execute the cd command.
 * @param {t_mini*} mini - The main structure of the shell.
 * @return {int} - Returns the result of set_directory if the directory 
 * change was successful, ERROR otherwise.
 */
int	mini_cd(t_mini *mini)
{
	char	*home;
	char	**args;

	mini->sig.status = SUCCESS;
	home = NULL;
	args = mini->cmd->args;
	if (args && args[1] && args[2])
	{
		ft_printfd(2, "%s: cd: too many arguments\n", mini->name);
		return (ERROR);
	}
	if (!args[1] || ft_strequ(args[1], "~") || ft_strequ(args[1], "--"))
	{
		home = get_env(mini->h_env, "HOME");
		if (!home)
		{
			ft_printfd(2, "%s: cd: HOME not set\n", mini->name);
			return (ERROR);
		}
		return (set_directory(mini, home, 1));
	}
	args[1] = add_home_path(mini, args[1]);
	return (s_path(mini));
}
