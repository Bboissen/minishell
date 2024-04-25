/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:24:55 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/25 18:03:19 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			path = ft_strjoin(tmp1, tmp2);
		}
	}
	else if (path && path[0] == '-' && !path[1])
		backward_dir(mini);
	ft_memdel(tmp1);
	ft_memdel(tmp2);
	return (path);
}

static int	change(t_mini *mini, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env(&mini->h_env, "OLDPWD", pwd);
			ft_memdel(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env(&mini->h_env, "PWD", pwd);
			ft_memdel(pwd);
		}
		return (SUCCESS);
	}
	return (ft_memdel(pwd), cd_err(mini, errno, path), ERROR);
}

int	backward_dir(t_mini *mini)
{
	char	*tmp;
	char	**args;

	args = mini->cmd->args;
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

int	mini_cd(t_mini *mini)
{
	char	*home;
	char	**args;
	t_sig	*sig;

	sig = get_sig();
	home = NULL;
	args = mini->cmd->args;
	if (arg_exists(args, 1))
		return (cd_err(mini, EXE, NULL), ERROR);
	if (!args || (ft_strequ(args[0], "~") && !args[1])
		|| (ft_strequ(args[0], "--") && !args[1]))
	{
		if (!get_env_value(mini, "HOME"))
			return (cd_err(mini, MISSING, "HOME"), ERROR);
		home = ft_strdup(get_env_value(mini, "HOME"));
		if (!home)
			return (error_manager(mini, MALLOC, NULL, NULL), ERROR);
		return (change(mini, home), SUCCESS);
	}
	if (args && args[0][0] == '-' && !args[0][1])
		return (backward_dir(mini), SUCCESS);
	if (access(args[0], F_OK) == -1)
		args[0] = add_home_path(mini, args[0]);
	change(mini, args[0]);
	return (SUCCESS);
}
