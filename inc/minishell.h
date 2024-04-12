/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/12 15:36:28 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes */

# include "../libft/includes/libft.h"
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
	END,
	JOIN,
	EXPAND
}	t_type;

typedef enum e_builtin
{
	NONE = 0,
	CD, //skip when pipe
	ECHO, //work with pipe
	ENV, //work with pipe
	EXIT, //work with pipe but output devnull
	EXPORT, //work with pipe without args
	PWD, //work with pipe
	UNSET, //skip when pipe
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
	DIRECTORY = 126,
	EXE = 127,
	MALLOC = 128,
	QUOTE = 129,
	PARSE = 130
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
	t_type			join;
	t_type			type;
	t_type			expand;
	int				quote;
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
	t_token			*token_h;
	t_token			*token;
	t_env			*env;
	t_cmd			*cmd_h;
	t_cmd			*cmd;
	t_sig			sig;
}	t_mini;

/* Functions */

void		redir(t_mini *mini, t_token *token, int type);
void		input(t_mini *mini, t_token *token);
int			minipipe(t_mini *mini);
char		*expansions(char *arg, t_env *env, int ret);

void		exec_cmd(t_mini *mini, t_token *token);
int			exec_bin(char **args, t_env *env, t_mini *mini);
int			exec_builtin(char **args, t_mini *mini);
int			is_builtin(char	*command);

int			mini_cd(char **args, t_env *env);
int			mini_echo(char **args);
int			mini_env(t_env *env);
void		mini_exit(t_mini *mini, char **cmd);
int			mini_export(char **args, t_env *env, t_env *secret);
int			mini_pwd(void);
int			mini_unset(char **args, t_mini *mini);

int			env_add(const char *value, t_env *env);
char		*get_env_name(char *dest, const char *src);
int			is_in_env(t_env *env, char *args);

void		parse(t_mini *mini);
t_token		*get_tokens(char *line);
void		squish_args(t_mini *mini);
int			is_last_valid_arg(t_token *token);
int			quotes(char *line, int index);
void		type_arg(t_token *token, int separator);
int			is_sep(char *line, int i);
int			ignore_sep(char *line, int i);

int			check_line(t_mini *mini, t_token *token);
char		*env_to_str(t_env *lst);
int			env_init(t_mini *mini, char **env_array);
void		init_mini(t_mini *mini, char **env);
char		*get_env_value(char *arg, t_env *env);
char		*env_value(char *env);
int			env_value_len(const char *env);
int			is_env_char(int c);
int			is_valid_env(const char *env);
void		print_sorted_env(t_env *env);
void		increment_shell_level(t_env *env);
size_t		size_env(t_env *lst);

void		reset_std(t_mini *mini);
void		close_fds(t_mini *mini);
void		ft_close(int fd);
void		reset_fds(t_mini *mini);

void		free_token(t_token *start);
void		free_env(t_env *env);
void		free_tab(char **tab);

t_token		*next_sep(t_token *token, int skip);
t_token		*prev_sep(t_token *token, int skip);
t_token		*next_run(t_token *token, int skip);
void		process_tokens(t_mini *mini);
void		update_token_pointers(t_token *token, t_token *prev);
void		update_mini_start(t_mini *mini, t_token *token);

int			is_type(t_token *token, int type);
int			is_types(t_token *token, char *types);
int			has_type(t_token *token, int type);
int			has_pipe(t_token *token);
t_token		*next_type(t_token *token, int type, int skip);

int			get_var_len(const char *arg, int pos, t_env *env, int ret);
int			arg_alloc_len(const char *arg, t_env *env, int ret);
char		*get_var_value(const char *arg, int pos, t_env *env, int ret);
int			handle_quotes(char *line, int *i, int *j, char *c);

void		sig_int(int code);
void		sig_quit(int code);
void		sig_init(void);

// lexer
int			is_spechar(char c);
int			is_space(int c);
int			is_spe_expand(char c);
char		*ft_strdup(const char *str);
int			lexer_err(int err, char c);
char		*syntax_check(t_mini *mini, t_token **token, char *str, int *quote);
char		*string_handler(t_mini *mini, t_token **token, char *str, int *quote);
char		*s_quote_handler(t_mini *mini, t_token **token, char *str, int *quote);
char		*d_quote_handler(t_mini *mini, t_token **token, char *str, int *quote);
char		*var_handler(t_mini *mini, t_token **token, char *str, int *quote);
char		*random_file(void);
#endif