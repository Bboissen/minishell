/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:32:57 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 18:35:50 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_env(const char *name)
{
	int		i;

	i = 0;
	if (!ft_strcmp(name, "") || ft_isdigit(name[i]) || name[i] == '=')
		return (FALSE);
	while (name[i] && (name[i] != '=' || name[i] != '\0'))
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
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
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
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

static int	is_in_env(t_env *env, char *name, char *value)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			if (env->value)
			{
				ft_memdel(env->value);
				env->value = ft_strdup(value);
			}
			return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

int	mini_export(t_mini *mini, t_cmd *cmd)
{
	t_env	*env;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	name = NULL;
	value = NULL;
	env = mini->h_env;
	if (!arg_exists(cmd->args, i))
		return (print_sorted_env(mini), SUCCESS);
	while (arg_exists(cmd->args, i))
	{
		name = malloc(sizeof(char) * BUFF_SIZE);
		if (!name)
			error_manager(mini, MALLOC, NULL, NULL);
		get_env_name(name, cmd->args[i]);
		if (!is_valid_env(name))
		{
			export_err(mini, EINVAL, cmd->args[i]);
			i++;
			continue ;
		}
		if (!ft_strcmp(name, "_"))
		{
			i++;
			continue ;
		}
		if (strchr(cmd->args[i], '='))
			value = ft_strdup(cmd->args[i] + ft_strlen(name) + 1);
		else
			value = NULL;
		if (!is_in_env(env, name, value))
			env_add(mini, name, value);
		free(name);
		if (value)
			free(value);
		i++;
	}
	return (get_sig()->status);
}
