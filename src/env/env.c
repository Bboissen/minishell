/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:43:56 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/21 21:10:53 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini(t_mini *mini, char **env)
{
	mini->cmd->in = dup(STDIN);
	mini->cmd->out = dup(STDOUT);
	mini->sig.status = 0;
	mini->sig.exit = 0;
	reset_fds(mini);
	env_init(mini, env);
	increment_shell_level(mini->env);
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst) + 1);
	if (!env)
		return (NULL);
	i = -1;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = -1;
			while (lst->value[++j])
				env[++i] = lst->value[j];
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (ERROR);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 0;
	while (env_array && env_array[0] && env_array[++i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (ERROR);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
	}
	return (SUCCESS);
}
