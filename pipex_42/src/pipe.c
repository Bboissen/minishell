/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:36:14 by bboissen          #+#    #+#             */
/*   Updated: 2024/02/11 11:49:32 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

pid_t	exec(t_list *lst, char **env, int fd_1, int fd_2)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd_1);
		dup2(fd_2, 1);
		close(fd_2);
		execve(((t_exec *)(lst->cont))->args[0],
			((t_exec *)(lst->cont))->args, env);
	}
	else if (pid > 0)
	{
		close(fd_2);
		dup2(fd_1, 0);
		close(fd_1);
		return (pid);
	}
	else
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

void	clean_fd(int files[2], int pipe_fd[2])
{
	close(files[0]);
	close(files[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	pipex(char **env, t_list *lst, int files[2])
{
	int		pipe_fd[2];
	int		i;
	int		size;
	t_list	*nxt;

	i = 0;
	size = ft_lstsize(lst);
	if (ft_lstsize(lst) == 1)
	{
		((t_exec *)(lst->cont))->pid = exec(lst, env, files[0], files[1]);
		return ;
	}
	pipe(pipe_fd);
	((t_exec *)(lst->cont))->pid = exec(lst, env, pipe_fd[0], pipe_fd[1]);
	while (i++ < size - 2)
	{
		pipe(pipe_fd);
		nxt = lst->next;
		((t_exec *)(nxt->cont))->pid = exec(nxt, env, pipe_fd[0], pipe_fd[1]);
		lst = nxt;
	}
	nxt = lst->next;
	pipe(pipe_fd);
	((t_exec *)(nxt->cont))->pid = exec(nxt, env, pipe_fd[0], files[1]);
	return (clean_fd(files, pipe_fd));
}

int	fd_handler(int argc, char **argv, char **env, t_list *lst)
{
	int		files[2];
	int		status;
	t_list	*current;

	files[0] = open(argv[1], O_RDONLY);
	if (files[0] < 0 || ft_lstsize(lst) < argc - 3)
	{
		close(files[0]);
		files[0] = open("/dev/null", O_RDONLY);
	}
	files[1] = open(argv[argc - 1], O_WRONLY);
	if (files[1] < 0)
		files[1] = open("/dev/null", O_WRONLY);
	current = lst;
	dup2(files[0], 0);
	close(files[0]);
	pipex(env, current, files);
	while (lst)
	{
		waitpid(((t_exec *)(lst->cont))->pid, &status, 0);
		lst = lst->next;
	}
	close(files[0]);
	close(files[1]);
	return (((status) & 0xff00) >> 8);
}
