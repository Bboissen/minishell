/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:16:09 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/07 09:40:28 by bboissen         ###   ########.fr       */
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
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE - 1)
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
void	get_env_value(t_mini *mini, char **value, char *name, char *arg)
{
	if (strchr(arg, '='))
	{
		*value = ft_strdup(arg + ft_strlen(name) + 1);
		if (!*value)
		{
			ft_memdel(name);
			error_manager(mini, MALLOC, NULL, NULL);
		}
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

/**
 * @brief Cleans up memory allocated for an exported environment variable.
 *
 * @param new A pointer to the new environment variable to be cleaned up.
 * @param name A pointer to the name of the environment variable.
 * @param value A pointer to the value of the environment variable.
 */
void	clean_export(t_env *new, char *name, char *value, int flag)
{
	ft_memdel(name);
	ft_memdel(value);
	if (flag)
		ft_memdel(new->name);
	ft_memdel(new);
}
