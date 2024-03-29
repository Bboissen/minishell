/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:17 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/28 15:12:30 by gdumas           ###   ########.fr       */
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
		input(mini);
	else if (is_type(prev, PIPE))
		*pipe = minipipe(mini);
}

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	pipe = 0;
	prev = prev_sep(token);
	next = next_sep(token);
	handle_redir(mini, token, prev, &pipe);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->token->skip == 0)
		exec_cmd(mini);
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
	t_token	*tmp;
	int		status;

	tmp = next_run(mini->cmd);
	if (is_types(mini->token, "TAI"))
		tmp = mini->token->next;
	while (mini->sig.exit == 0 && tmp)
	{
		redir_and_exec(mini, tmp);
		reset_and_wait(mini, &status);
		if (mini->last == 0)
			mini->sig.status = status;
		if (mini->parent == 0)
		{
			free_token(mini->token);
			exit(mini->sig.status);
		}
		mini->token->skip = 0;
		tmp = next_run(tmp);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	if (ac != 1)
		return (ERROR);
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	init_mini(&mini, env, av[0]);
	/*hardcode_parser;*/
	/*exec*/

	// while (!mini.sig.exit)
	// {
	// 	sig_init(&mini);
	// 	/*lexer(&mini);*/
	// 	parser(&mini);
	// 	if (mini.cmd)
	// 		minishell(&mini);
	// 	free_token(mini.token);
	// 	free_cmd(mini.cmd);
		
	// }*/
	clean_exit(&mini);
	return (mini.sig.status);
}
