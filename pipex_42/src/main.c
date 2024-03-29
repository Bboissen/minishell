/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:41:26 by bboissen          #+#    #+#             */
/*   Updated: 2024/02/11 13:11:37 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

static int	cmd_nester(char const *s, t_list **pipe, char **argv, char **env);
static int	access_handler(t_list **pipe, int argc, char **argv, char **env);

int	main(int argc, char **argv, char **env)
{
	t_list	*pipe;
	int		i;
	int		err;
	void	(*fun_ptr)(t_list*, int);

	if (argc < 5 || argc > 5)
		exit (EXIT_FAILURE);
	fun_ptr = clr_content;
	pipe = NULL;
	i = 2;
	err = access_handler(&pipe, argc, argv, env);
	if (ft_lstsize(pipe) > 0 && (err == 0 || err == 1))
		err = fd_handler(argc, argv, env, pipe);
	if (err == MALLOC_KO)
		printf_fd(2, "Memory allocation failed\n");
	ft_lstclear(&pipe, fun_ptr, 1);
	exit (err);
}

static int	access_handler(t_list **pipe, int argc, char **argv, char **env)
{
	int		i;
	int		err;
	int		err_file;
	int		ac;

	ac = argc;
	err_file = check_infile(argc, argv);
	i = 2;
	if (err_file == 2 || err_file == 13)
		i++;
	err = cmd_nester(argv[i++], pipe, argv, env);
	err_file = check_outfile(ac, argv);
	if (err_file == 1)
		argc -= 1;
	while (i < argc - 1 && err != MALLOC_KO)
	{
		err = cmd_nester(argv[i], pipe, argv, env);
		i++;
	}
	if (err_file == 1 && err != MALLOC_KO)
		err = err_file;
	return (err);
}

static int	cmd_nester(char const *s, t_list **pipe, char **argv, char **env)
{
	t_list		*cmd;
	t_exec		*exec;
	int			err;

	if (!s[0])
		return (printf_fd(2, "%s: command not found\n", &argv[0][2]), 127);
	cmd = NULL;
	exec = (t_exec *)malloc(sizeof(t_exec));
	if (exec == NULL)
		return (MALLOC_KO);
	exec->args = parse_words(s, &cmd, argv, env);
	if (cmd)
		exec->err = ((t_word *)((cmd)->cont))->err;
	else
		exec->err = MALLOC_KO;
	err = exec->err;
	if (cmd)
		clear_cmd(NULL, &cmd, 0);
	if (exec->args)
		ft_lstadd_back(pipe, ft_lstnew(exec));
	else
		free(exec);
	return (err);
}
