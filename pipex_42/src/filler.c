/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:47:59 by bboissen          #+#    #+#             */
/*   Updated: 2024/02/11 11:48:28 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	index_srch(const char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-2);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	if (i == 0)
		return (-1);
	return (-2);
}

char	*fill_cmd(char const *s, t_list **cmd, char **argv, char **env)
{
	char		*args;
	static int	i = 0;

	if (i++ == 0)
		args = check_perm(s, cmd, argv, env);
	else if (index_srch(s, '"') < 0)
	{
		args = ft_substr(s, ((t_word *)((*cmd)->cont))->start,
				((t_word *)((*cmd)->cont))->len);
	}
	else
		args = ft_substr(s, ((t_word *)((*cmd)->cont))->start + 1,
				((t_word *)((*cmd)->cont))->len - 2);
	if (args == NULL && i > 1)
		((t_word *)((*cmd)->cont))->err = MALLOC_KO;
	if (ft_lstsize(*cmd) == 1 || args == NULL)
		i = 0;
	return (args);
}
