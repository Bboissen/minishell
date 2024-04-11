/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/11 15:53:13 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*to delete*/
/**
 * Calculate the length of the environment array.
 * @param {char**} env - The environment array.
 * @return {int} - Returns the length of the environment array.
 */
int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/**
 * Sort an array of strings in ascending order.
 * @param {char**} tab - The array to sort.
 * @param {int} env_len - The length of the array.
 */
void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = FALSE;
	while (tab && ordered == FALSE)
	{
		i = -1;
		while (++i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = TRUE;
			}
		}
		env_len--;
	}
}

/*plutot faire env_to_tab*/
/**
 * Print the environment variables in sorted order.
 * @param {t_env*} env - The environment to print.
 */
void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tab, str_env_len(tab)); //lst size
	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(tab[i]);
		i++;
	}
	free_tab(tab);
}
