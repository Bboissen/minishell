/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:16:09 by talibabtou        #+#    #+#             */
/*   Updated: 2024/05/04 11:44:47 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extracts the name of the environment variable from a string.
 * 
 * @param dest Pointer to the destination string where the name
 * will be stored.
 * @param src Pointer to the source string from which the name
 * will be extracted.
 * @return {char *} - Returns a pointer to the destination string.
 */
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

/**
 * @brief Extracts the value of the environment variable from a string.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param value Double pointer to the string where the value will be stored.
 * @param arg Pointer to the string from which the value will be extracted.
 * @param name Pointer to the name of the environment variable.
 */
void	get_env_value(t_mini *mini, char **value, char *arg, char *name)
{
	if (strchr(arg, '='))
	{
		*value = ft_strdup(arg + ft_strlen(name) + 1);
		if (!*value)
			return (error_manager(mini, MALLOC, NULL, NULL),
				ft_memdel(name), ERROR);
	}
	else
		*value = NULL;
}

/**
 * @brief Checks if a string is a valid environment variable name.
 * 
 * @param name Pointer to the string to be checked.
 * @return {int} - Returns TRUE if the string is a valid
 * environment variable name, FALSE otherwise.
 */
int	is_valid_env(const char *name)
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
