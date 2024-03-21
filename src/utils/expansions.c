/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:44:41 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/18 18:10:01 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ret_size(int ret)
{
	char	*tmp;
	int		ret_len;

	tmp = ft_itoa(ret);
	ret_len = ft_strlen(tmp);
	ft_memdel(tmp);
	return (ret_len);
}

static char	*get_var_name(const char *arg, int *pos)
{
	static char	var_name[BUFF_SIZE];
	int			i;

	i = 0;
	while (arg[*pos] && is_env_char(arg[*pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[*pos];
		(*pos)++;
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

int	get_var_len(const char *arg, int pos, t_env *env, int ret)
{
	char	*var_name;
	char	*var_value;
	int		len;

	len = 0;
	if (arg[pos] == '?')
		return (ret_size(ret));
	if (len != -1)
		return (len);
	if (ft_isdigit(arg[pos]))
		return (0);
	var_name = get_var_name(arg, &pos);
	var_value = get_env_value(var_name, env);
	len = ft_strlen(var_value);
	ft_memdel(var_value);
	return (len);
}

int	arg_alloc_len(const char *arg, t_env *env, int ret)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

char	*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	*var_name;
	char	*var_value;

	if (arg[pos] == '?')
		return (ft_itoa(ret));
	if (ft_isdigit(arg[pos]))
		return (NULL);
	var_name = get_var_name(arg, &pos);
	var_value = get_env_value(var_name, env);
	return (var_value);
}
