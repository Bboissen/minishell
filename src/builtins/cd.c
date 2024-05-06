/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:24:55 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/06 17:08:49 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change(t_mini *mini, char *path);
static int	backward_dir(t_mini *mini);

/**
 * @brief Changes the current directory to the one specified
 * in the arguments, or to the home directory if no arguments are given.
 *
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @return {int} - SUCCESS if the directory was changed successfully,
 * ERROR otherwise.
 */
int	mini_cd(t_mini *mini, t_cmd *cmd)
{
	char	**args;
	char	*home;

	args = cmd->args;
	home = return_env_value(mini, "HOME");
	if (arg_exists(args, 1) && !ft_strequ(args[0], "--"))
		return (cd_err(mini, ERROR, NULL), ERROR);
	else if (arg_exists(args, 1) && ft_strequ(args[0], "--"))
		args++;
	if (arg_exists(args, 0) && args[0][0] == '\0')
		return (SUCCESS);
	if (args && args[0][0] == '-' && !args[0][1])
		return (backward_dir(mini));
	if (arg_exists(args, 0))
		return (change(mini, args[0]));
	if (!home)
		return (cd_err(mini, MISSING, "HOME"), ERROR);
	else
		return (change(mini, home));
}

/**
 * @brief Changes the current directory to the given path and 
 * updates the PWD and OLDPWD environment variables.
 *
 * @param mini The main structure of the minishell.
 * @param path The path to change to.
 * @return {int} - SUCCESS if the directory was changed successfully,
 * ERROR otherwise.
 */
static int	change(t_mini *mini, char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_strdup(return_env_value(mini, "PWD"));
	if (!old_pwd)
		return (error_manager(mini, MALLOC, NULL, NULL), ERROR);
	if (chdir(path) == 0)
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			set_env(mini, &mini->h_env, "PWD", new_pwd);
			ft_memdel(new_pwd);
		}
		if (old_pwd)
		{
			set_env(mini, &mini->h_env, "OLDPWD", old_pwd);
			ft_memdel(old_pwd);
		}
		return (SUCCESS);
	}
	else
		ft_memdel(old_pwd);
	return (cd_err(mini, errno, path), ERROR);
}

/**
 * @brief Changes the current directory to the previous one
 * stored in the OLDPWD environment variable.
 *
 * @param mini The main structure of the minishell.
 * @return {int} - ERROR if the command was '-',
 * SUCCESS otherwise.
 */
static int	backward_dir(t_mini *mini)
{
	char	*tmp;

	tmp = return_env_value(mini, "OLDPWD");
	if (!tmp)
		return (cd_err(mini, MISSING, "OLDPWD"), ERROR);
	else
	{
		tmp = return_env_value(mini, "OLDPWD");
		ft_printfd(STDOUT_FILENO, "%s\n", tmp);
		return (change(mini, tmp));
	}
}
