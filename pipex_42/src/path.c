/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:31:05 by bboissen          #+#    #+#             */
/*   Updated: 2024/02/11 11:49:28 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static char	*path_checker(char const *s, char	*str, char	**path, int *check)
{
	char	*buff;
	int		i;

	i = -1;
	while (path[++i] && *check == -1)
	{
		*check = 0;
		buff = ft_strjoin(path[i], "/");
		if (buff == NULL)
			return (NULL);
		str = ft_strjoin(buff, s);
		if (str == NULL)
		{
			free(buff);
			return (NULL);
		}
		*check = access(str, X_OK);
		if (*check == -1)
			free(str);
		free(buff);
	}
	if (*check == -1)
		return (NULL);
	else
		return (str);
}

char	*path_finder(char const *s, t_list **cmd, char **env)
{
	int		i;
	int		check;
	char	*str;
	char	**path;

	i = -1;
	check = -1;
	str = NULL;
	while (env[++i] && str == NULL)
		str = ft_strnstr(env[i], "PATH", 4);
	if (str == NULL)
		return (NULL);
	i = -1;
	path = ft_split(str + 5, ':');
	if (path)
	{
		str = path_checker(s, str, path, &check);
		free_array(path);
	}
	if (path == NULL || (str == NULL && check == 0))
		return (((t_word *)((*cmd)->cont))->err = MALLOC_KO, NULL);
	if (check == -1)
		return (((t_word *)((*cmd)->cont))->err = errno, NULL);
	return (str);
}

char	*cmd_finder(char const *s, t_list **cmd, char **argv, char **env)
{
	char	*temp;
	char	*str;

	str = NULL;
	temp = ft_substr(s, ((t_word *)((*cmd)->cont))->start,
			((t_word *)((*cmd)->cont))->len);
	if (temp)
		str = path_finder(temp, cmd, env);
	if (temp)
		free(temp);
	if (!str && ((t_word *)((*cmd)->cont))->err == MALLOC_KO || !temp)
	{
		((t_word *)((*cmd)->cont))->err = MALLOC_KO;
		return (str);
	}
	if (str == NULL)
	{
		((t_word *)((*cmd)->cont))->err = CMD_KO;
		printf_fd(2, "%s: command not found: %s\n", &argv[0][2], s);
	}
	return (str);
}
