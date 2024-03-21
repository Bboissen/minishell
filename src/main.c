/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:36:58 by bboissen          #+#    #+#             */
/*   Updated: 2024/03/21 13:26:00 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*<infile1 grep a >outfile1 | <infile1 cat >outfile2 | <infile2 sed "s/And/But/" | grep But | cat >outfile3 | cat*/
/*<infile1 cat | mkdir break | cd break >outfile1*/
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_cmd
{
    char    		**args;
    char    		*in;
    char    		 *out;
    int     		fdin;
    int				fdout;
    int				pid;
    struct s_cmd	*prev;
    struct s_cmd	*next;
}   t_cmd;

t_cmd *init_struct(t_cmd *prev, char **args, char *in, char *out)
{
	t_cmd	*cmd;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = args;
	cmd->in = in;
	cmd->out = out;
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->pid = -1;
	cmd->prev = prev;
	cmd->next = NULL;
	if (prev)
		prev->next = cmd;
	return (cmd);
}

int	main(void)
{
	t_cmd	*cmd;
	t_cmd	*head;
	t_cmd	*tail;
	char	*args1[3] = {"/usr/bin/grep", "a", NULL};
	char	*args2[2] = {"/usr/bin/cat", NULL};
	char	*args3[3] = {"/usr/bin/sed", "s/And/But/", NULL};
	char	*args4[3] = {"/usr/bin/grep", "But", NULL};
	char	*args5[2] = {"/usr/bin/cat", NULL};
	char	*args6[2] = {"/usr/bin/cat", NULL};

	cmd = init_struct(NULL, args1, "infile1", "outfile1");
	head = cmd;
	cmd->next = init_struct(cmd, args2, "infile1", "outfile2");
	cmd = cmd->next;
	cmd->next = init_struct(cmd, args3, "infile2", NULL);
	cmd = cmd->next;
	cmd->next = init_struct(cmd, args4, NULL, NULL);
	cmd = cmd->next;
	cmd->next = init_struct(cmd, args5, NULL, "outfile3");
	cmd = cmd->next;
	cmd->next = init_struct(cmd, args6, NULL, NULL);

	while (head)
	{
		printf("args: %s\n", head->in);
		if (head->next)
			head = head->next;
		else
		{
			tail = head;
			break ;
		}
	}
	printf("------------\n");
	head = tail;
	while (head)
	{
		printf("args: %s\n", head->in);
		head = head->prev;
	}
	return (0);
}