
#include "minishell.h"

int	path_finder(t_mini *mini, t_cmd **cmd, char *str)
{
	t_env	*local_env;
	int		err;
	char	*args;
	char	**path;

	args = NULL;
	local_env = mini->h_env;
	while (local_env && ft_strcmp(local_env->name, "PATH"))
		local_env = local_env->next;
	if (!local_env)
		return (0);
	path = ft_split(local_env->value, ':');
	if (path)
	{
		args = path_checker(str, args, path, &err);
		free_tab(path);
	}
	if (path == NULL || (args == NULL && err == 0))
		return (free_cmd(cmd), error_manager(mini, MALLOC, NULL, NULL));
	else if (err == -1)
		return (err);
	else
		cmd_filler(mini, cmd, args);
	return (0);
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