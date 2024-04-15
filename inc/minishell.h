/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/15 16:21:46 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes */

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Defines */

# define BUFF_SIZE 4096
# define PATH_MAX 4096

# define ERROR_LEX "" //to define, etc..

typedef enum e_type
{
	EMPTY = 0,
	STR,
	VAR,
	TRUNC,
	APPEND,
	INPUT,
	HEREDOC,
	PIPE,
	END,
	JOIN,
	EXPAND
}	t_type;

typedef enum e_builtin
{
	NONE = 0,
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
}	t_builtin;

typedef enum e_io
{
	STDIN = 0,
	STDOUT,
	STDERR
}	t_io;

typedef enum e_bool
{
	FALSE = 0,
	TRUE
}	t_bool;

typedef enum e_error
{
	SUCCESS = 0,
	ERROR = 1,
	STX = 2,
	DIRECTORY = 126,
	CMD = 127,
	MALLOC = 128,
	INTERUPT = 130,
	QUIT = 131
}	t_error;

/* Structures */

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_sig
{
	int				status;
	int				sigint;
	int				sigquit;
	int				exit;
}	t_sig;

typedef struct s_token
{
	char			*str;
	int				type;
	int				expand;
	int				join;
	int				skip;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*in;
	char			*out;
	int				fd[2];
	int				pid;
	t_builtin		builtin;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_mini
{
	char			*name;
	t_token			*h_token;
	t_token			*token;
	t_env			*h_env;
	t_env			*env;
	t_cmd			*h_cmd;
	t_cmd			*cmd;
	t_sig			sig;
}	t_mini;

/* Builtin */

int		is_builtin(t_mini *mini);
void	exec_builtin(char **args, t_mini *mini);
int		mini_cd(t_mini *mini);
int		mini_echo(t_mini *mini);
int		mini_env(t_mini *mini);
int		mini_exit(t_mini *mini);
int		mini_export(char **args, t_env *env, t_env *secret);
int		mini_pwd(void);
int		mini_unset(t_mini *mini);

/* Env */

int		init_env(t_mini **mini, char **env_array);
void	increment_shell_level(t_mini **mini);
char	**env_to_tab(t_env *env_lst);
char	*get_env(t_env *env, char *name);
void	set_env(t_env **env, char *name, char *value);
void	print_sorted_env(t_env *env);
void	sort_env(char **tab, int env_len);
void	expand_join(t_mini **mini);
char	*expand_token(t_mini **mini, char *str);
t_token	*list_join(t_token *token);

/* Init */

void	readline_setup(char *rl, char *str);
void	init_mini(t_mini **mini, char **env, char *name);
void	reinit(t_mini *mini, char *rl);

/* Exec */

int		cmd_exec(t_mini *mini);
void	pipex(t_mini *mini);
void	fd_handler(t_mini *mini);
pid_t	exec(t_mini *mini);

/* Stds & fds */

void	ft_close(int fd);
void	close_fds(int *fd);
void	reset_fds(t_mini *mini);
void	reset_std(t_mini *mini);

/* Free */

void	free_token(t_token *start);
void	free_env(t_env *env);
void	free_tab(char **tab);
void	free_cmd(t_cmd *cmd);
int		clean_exit(t_mini *mini);

/* Signals */

void	sig_int(t_mini *mini, int code);
void	sig_quit(t_mini *mini, int code);
void	sig_init(t_mini *mini);

#endif