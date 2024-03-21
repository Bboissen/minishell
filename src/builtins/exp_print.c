/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:19:06 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/21 13:02:16 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_env(void)
{
	char	**dup;
	size_t	count;

	count = (get_envs_count());
	dup = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	dup[count] = 0;
	count--;
	while (count != (unsigned long)-1)
	{
		dup[count] = ft_strdup(g_envs[count]);
		count--;
	}
	return (dup);
}

static t_env	*dup_env(t_mini *mini)
{
	t_env	*current;
	t_env	*dup;
	size_t	count;

	current = mini->env;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	dup = (t_env *)malloc(sizeof(t_env *) * (count + 1));
	if (!dup)
		return (NULL);
	dup[count] = 0;
	current = mini->env;
	count--;
	while (current != NULL)
	{
		dup[count] = (t_env *)malloc(sizeof(t_env));
		dup[count].name = strdup(current->name);
		dup[count].value = strdup(current->value);
		count--;
		current = current->next;
	}
	return (dup);
}

static void	print_export(char **export)
{
	size_t	i;
	size_t	j;
	char	equ;

	i = 0;
	while (export[i])
	{
		equ = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (export[i][j])
		{
			ft_putchar_fd(export[i][j], 1);
			if (export[i][j] == '=' && equ)
			{
				ft_putchar_fd('"', 1);
				equ--;
			}
			j++;
		}
		if (!equ)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	sort_env(void)
{
	char	**dup;
	char	*tmp;
	size_t	i;
	size_t	j;

	dup = dup_env();
	i = 0;
	while (dup[i++])
	{
		j = i + 1;
		while (dup[j++])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
		}
	}
	print_export(dup);
	ft_free_array(dup);
}

int	check_export_name(char *args)
{
	size_t	i;
	char	alpha_found;

	i = 0;
	alpha_found = 0;
	if (!args || !args[0] || args[0] == '=')
		return (0);
	while (args[i] && args[i] != '=')
	{
		if (ft_isalpha(args[i]))
			alpha_found = 1;
		else
		{
			if (ft_isdigit(args[i]) && !alpha_found)
				return (0);
			else if (!ft_isdigit(args[i]) && args[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}
