/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:24:55 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/21 15:37:44 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*env_value;
	int		i;
	int		j;
	int		s_alloc;

	while (env != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			env_value = malloc(sizeof(char) * s_alloc + 1);
			if (!env_value)
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
				if (i > (int)len)
					env_value[j++] = env->value[i];
			env_value[j] = '\0';
			return (env_value);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (!is_in_env(env, oldpwd))
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			return (ft_putendl_fd
				("minishell: cd: HOME not set", STDERR), ERROR);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			return (ft_putendl_fd
				("minishell: cd: OLDPWD not set", STDERR), ERROR);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	return (ft_memdel(env_path), ret);
}

int	mini_cd(char **args, t_env *env)
{
	int		cd_ret;

	if (!args[1])
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}*/

static char	*add_home_path(char *path)
{
	char	*tmp1;
	char	*tmp2;

	if (!ft_strncmp(path, "~/", 2))
	{
		tmp1 = get_env("HOME");
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

static int	change(char *path, int home)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", pwd);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env("PWD", pwd);
			free(pwd);
		}
		if (home)
			free(path);
		return (ERROR);
	}
	return (free(pwd), SUCCESS);
}

static int	set_directory(t_mini *mini, char *path, int home)
{
	struct stat	st;

	if (change(path, home))
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
	ft_printfd(2, '\n');
	if (home)
		free(path);
	return (SUCCESS);
}

static int	s_path(t_mini *mini)
{
	char	*tmp;
	char	**args;

	args = mini->cmd->args;
	if (ft_strequ(args[1], "-"))
	{
		tmp = get_env("OLDPWD");
		if (tmp)
		{
			set_directory(mini, tmp, 0);
			free(tmp);
		}
		tmp = get_env("PWD");
		if (tmp)
		{
			ft_printfd(1, "%s\n", tmp);
			free(tmp);
		}
		return (ERROR);
	}
	return (set_directory(mini, args[1], 0));
}

int	mini_cd(t_mini *mini)
{
	char	*home;
	char	**args;

	mini->sig.status = SUCCESS;
	home = NULL;
	args = mini->cmd->args;
	if (args && args[1] && args[2])
	{
		ft_printfd(2, "minishell: cd: too many arguments\n");
		return (ERROR);
	}
	if (!args[1] || ft_strequ(args[1], "~") || ft_strequ(args[1], "--"))
	{
		home = get_env("HOME");
		if (!home)
		{
			ft_printfd(2, "minishell: cd: HOME not set\n");
			return (ERROR);
		}
		return (set_directory(mini, home, 1));
	}
	args[1] = add_home_path(args[1]);
	return (s_path(args));
}
