/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:47:51 by bboissen          #+#    #+#             */
/*   Updated: 2024/02/11 13:01:52 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

# define PERM_KO 126
# define CMD_KO 127
# define WRITE_KO 1
# define MALLOC_KO 128

typedef struct s_list
{
	void			*cont;
	struct s_list	*next;
}	t_list;

typedef struct s_exec
{
	char	**args;
	int		pid;
	int		err;
}	t_exec;

typedef struct s_word
{
	int		start;
	int		len;
	int		err;
}	t_word;

size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		printf_fd(int fd, const char *format, ...);
char	**ft_split(char const *s, char c);

void	free_array(char **list);
void	clr_content(t_list *lst, int type);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(t_list *, int), int type);
void	ft_lstadd_back(t_list **lst, t_list *new);

int		fd_handler(int argc, char **argv, char **env, t_list *lst);
int		check_infile(int argc, char **files);
int		check_outfile(int argc, char **files);
char	*cmd_finder(char const *s, t_list **cmd, char **argv, char **env);
char	**clear_cmd(char **args, t_list **cmd, int mode);
char	*check_perm(char const *s, t_list **cmd, char **argv, char **env);
char	**parse_words(char const *s, t_list **cmd, char **argv, char **env);
char	*fill_cmd(char const *s, t_list **cmd, char **argv, char **env);

#endif