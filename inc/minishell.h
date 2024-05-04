/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 11:58:30 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes */

# include "libft.h"
# include "printf.h"
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

typedef enum e_bool
{
	FALSE = 0,
	TRUE
}	t_bool;

typedef enum e_error
{
	END = 0,
	SUCCESS = 0,
	ERROR = 1,
	PARSE = 2,
	SYNTAX = 2,
	MISSING = 125,
	X_PERM = 126,
	DIRECTORY = 126,
	EXE = 127,
	MALLOC = 128,
	QUOTE = 129,
	INTERUPT = 130,
	QUIT = 131,
	OPEN = 133,
	READ = 134,
	FCT = 135,
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
	int				working;
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
	char			*rl;
	t_token			*h_token;
	t_token			*token;
	t_env			*h_env;
	t_env			*env;
	t_cmd			*h_cmd;
	t_cmd			*cmd;
}	t_mini;

/* Builtin */

int			mini_cd(t_mini *mini, t_cmd *cmd);
int			mini_echo(t_mini *mini, t_cmd *cmd);
int			mini_env(t_mini *mini, t_cmd *cmd);
int			mini_exit(t_mini *mini, t_cmd *cmd);
int			mini_export(t_mini *mini, t_cmd *cmd);
int			mini_pwd(t_mini *mini, t_cmd *cmd);
int			mini_unset(t_mini *mini, t_cmd *cmd);

/* Env */

t_sig		*get_sig(void);
char		**env_to_tab(t_mini *mini);
char		*get_env_value(t_mini *mini, char *name);
void		set_env(t_env **env, char *name, char *value);
void		print_sorted_env(t_mini *mini);
void		expand_join(t_mini **mini);
char		*expand_token(t_mini **mini, char *str);
t_token		*list_join(t_mini *mini, t_token *token);

/* Init */

void		init_mini(t_mini **mini, char **env, char *name);
int			init_env(t_mini **mini, char **env_array);
void		increment_shell_level(t_mini **mini);
void		sig_init(void);
void		readline_setup(t_mini *mini, char **rl, char *str);
void		reinit(t_mini **mini);

/* Exec */

void		cmd_exec(t_mini *mini);
int			cmd_size(t_cmd *h_cmd);
int			exec_builtin(t_mini *mini, t_cmd *cmd);
void		fd_handler(t_mini *mini, t_cmd *cmd);
int			arg_exists(char **args, int index);

/* Stds & fds */

void		close_fds(int *fd);
void		delete_heredoc(t_mini *mini);

/* Free */

void		free_token(t_token **token);
void		free_env(t_env *env);
void		free_tab(char **tab);
void		free_cmd(t_cmd **cmd);
int			clean_exit(t_mini *mini);

/* Signals */

void		sig_handler(int code);

/* Errors */
int			error_manager(t_mini *mini, int err, char *fct, char *str);
int			export_err(t_mini *mini, int error, char *arg);
void		cd_err(t_mini *mini, int err, char *arg);

// lexer
void		lexer(t_mini *mini);
int			is_spechar(char c);
int			is_space(int c);
int			is_spe_builtin(char *str);
int			is_spe_expand(char c);
void		lexer_err(t_mini *mini, char *str, int err, char c);
char		*syntax_check(t_mini *mini, char *str, int *quote);
char		*string_handler(t_mini *mini, char *str, int *quote);
char		*s_quote_handler(t_mini *mini, char *str, int *quote);
char		*d_quote_handler(t_mini *mini, char *str, int *quote);
char		*var_handler(t_mini *mini, char *str, int *quote);
char		*random_file(t_mini *mini);

//heredoc
void		heredoc(t_mini *mini);
char		*expand_line(t_mini *mini, char *str, int fd);
void		delete_heredoc(t_mini *mini);

//parser
void		parser(t_mini *mini);
void		cmd_skip(t_mini *mini, t_cmd **cmd, t_token **token);
void		new_cmd(t_mini **mini, t_cmd **cmd, int *arg_flag);
char		**add_args(t_mini *mini, t_cmd **cmd, char *str);
t_builtin	check_blt(t_cmd **cmd, char *str, int *arg_flag);
int			path_finder(t_mini *mini, t_cmd **cmd, char *str);
void		parser_err(t_mini *mini, char *str, int err);

#endif