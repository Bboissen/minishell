/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:29 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/19 11:24:22 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	varlcpy(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

void	increment_index(t_exp *ex, char *arg)
{
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	else
		if (arg[ex->j - 1] != '?')
			ex->j++;
}

void	insert_var(t_exp *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret);
	if (env_value)
		ex->i += varlcpy(ex->new_arg, env_value, ex->i);
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	increment_index(ex, arg);
}

static void	handle_expansion(t_exp *ex, char *arg, t_env *env, int ret)
{
	ex->j++;
	if ((arg[ex->j] == '\0' || ft_isalnum(arg[ex->j]) == 0)
		&& arg[ex->j] != '?')
		ex->new_arg[ex->i++] = '$';
	else
		insert_var(ex, arg, env, ret);
}

char	*expansions(char *arg, t_env *env, int ret)
{
	t_exp	ex;
	int		new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	ex.new_arg = malloc(sizeof(char) * new_arg_len + 1);
	if (ex.new_arg == NULL)
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION)
			handle_expansion(&ex, arg, env, ret);
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
