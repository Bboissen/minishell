/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/19 14:17:07 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redir(t_mini *mini, t_token *token, t_token *prev, int *pipe)
{
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, PIPE))
		*pipe = minipipe(mini);
}

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	pipe = 0;
	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	handle_redir(mini, token, prev, &pipe);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	reset_and_wait(t_mini *mini, int *status)
{
	reset_std(mini);
	close_fds(mini);
	reset_fds(mini);
	waitpid(-1, status, 0);
	*status = WEXITSTATUS(*status);
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;

	token = next_run(mini->start, NOSKIP);
	if (is_types(mini->start, "TAI"))
		token = mini->start->next;
	while (mini->exit == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		redir_and_exec(mini, token);
		reset_and_wait(mini, &status);
		if (mini->last == 0)
			mini->ret = status;
		if (mini->parent == 0)
		{
			free_token(mini->start);
			exit(mini->ret);
		}
		mini->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	init_mini(&mini, env);
	while (!mini.exit)
	{
		sig_init();
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		free_token(mini.start);
	}
	free_env(mini.env);
	free_env(mini.secret_env);
	return (mini.ret);
}
