/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/06 16:56:50 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **tab, int env_len);
static int	str_env_len(char **env_tab);

/**
 * @brief Print the environment variables in sorted order.
 * 
 * @param env The environment to print.
 */
void	print_sorted_env(t_mini *mini)
{
	int		i;
	int		len;
	char	delim;
	char	**tab;

	tab = env_to_tab(mini);
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		len = ft_strchr(tab[i], '=') - tab[i];
		delim = tab[i][len];
		tab[i][len] = '\0';
		ft_printfd(STDOUT_FILENO, "declare -x %s", tab[i]);
		if (delim)
		{
			ft_printfd(STDOUT_FILENO, "%s", "=\"");
			ft_printfd(STDOUT_FILENO, "%s", tab[i] + len + 1);
			ft_printfd(STDOUT_FILENO, "\"\n");
		}
		i++;
	}
	free_tab(tab);
}

/**
 * @brief Sort an array of strings in ascending order.
 * 
 * @param tab The array to sort.
 * @param env_len The length of the array.
 */
static void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = FALSE;
	while (!ordered)
	{
		ordered = TRUE;
		i = -1;
		while (++i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = FALSE;
			}
		}
		env_len--;
		if (env_len == 0)
			ordered = TRUE;
	}
}

/**
 * @brief Calculate the length of the string environment array.
 *
 * @param env_tab An array of strings representing the environment.
 * @return {int} - The number of elements in the env_tab array.
 */
static int	str_env_len(char **env_tab)
{
	int	i;

	i = 0;
	while (env_tab[i])
		i++;
	return (i);
}

/**
 * @brief Updates an environment variable in the environment list.
 * 
 * @param env The pointer to the environment list.
 * @param name The name of the environment variable to set.
 * @param value The value to set the environment variable to.
 */
int	set_env(t_mini *mini, t_env **env, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == SUCCESS)
		{
			ft_memdel(tmp->value);
			if (value)
			{
				tmp->value = strdup(value);
				if (!tmp->value)
				{
					ft_memdel(value);
					ft_memdel(name);
					error_manager(mini, MALLOC, NULL, NULL);
				}
				return (TRUE);
			}
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

/**
 * @brief Retrieves the value of an environment variable by its name.
 * 
 * @param env The environment list.
 * @param name The name of the environment variable.
 * @return {char*} - Returns the value of the environment variable if
 * found, NULL otherwise.
 */
char	*return_env_value(t_mini *mini, char *name)
{
	t_env	*env;

	env = mini->h_env;
	while (env != NULL)
	{
		if (strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
