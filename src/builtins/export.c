/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:32:57 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/30 17:23:20 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_env(const char *name)
{
	int		i;

	i = 0;
	if (!ft_strcmp(name, "") || ft_isdigit(name[i]) || !ft_strcmp(name, "="))
		return (FALSE);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	env_add(t_mini *mini, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		error_manager(mini, MALLOC, NULL, NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (mini->env == NULL)
	{
		mini->env = new;
		mini->h_env = new;
	}
	else
	{
		tmp = mini->env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
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
		get_env_name(env_name, env->name);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			if (env->value)
			{
				ft_memdel(env->value);
				env->value = ft_strdup(args);
			}
			return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

int	mini_export(t_mini *mini)
{
	t_env	*env;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	name = NULL;
	value = NULL;
	env = mini->h_env;
	if (!arg_exists(mini->cmd->args, i))
		return (print_sorted_env(mini), SUCCESS);
	while (arg_exists(mini->cmd->args, i++))
	{
		name = malloc(sizeof(char) * BUFF_SIZE);
		if (!name)
			error_manager(mini, MALLOC, NULL, NULL);
		get_env_name(name, mini->cmd->args[0]);
		if (!is_valid_env(name))
			export_err(mini, EINVAL, mini->cmd->args[0]);
		value = ft_strdup(mini->cmd->args[0] + ft_strlen(name) + 1);
		if (!is_in_env(env, name))
			env_add(mini, name, value);
		free(name);
		free(value);
	}
	return ;
}
