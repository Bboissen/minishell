/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:32:57 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/29 18:09:24 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_env(const char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]))
		return (FALSE);
	while (env[i] && env[i] != '=')
	{
		if (!ft_isalnum(env[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

char	*get_env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			if (env->value)
				ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

int	mini_export(t_mini *mini)
{
	t_env	*env;
	char	**args;

	env = mini->h_env;
	args = mini->cmd->args;
	if (!arg_exists(args, 0))
		print_sorted_env(mini->h_env);
	else if (arg_exists(args, 0))
	{
		if (!is_valid_env(args[0]) || args[0][0] == '=')
			return (export_err(mini, 22, args[0]), EINVAL);
		if (!is_in_env(env, args[0]))
			env_add(args[0], mini->h_env);
	}
	return (SUCCESS);
}
