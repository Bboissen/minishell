/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:32:57 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/04 17:34:04 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_args(t_mini *mini, t_cmd *cmd, t_env **env, int *i);
static int	env_add(t_mini *mini, char *name, char *value);
static int	add_env_to_list(t_mini *mini, t_env *new);

/**
 * @brief Executes the export command in a mini shell.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @return {int} - Returns the status of the command execution.
 */
int	mini_export(t_mini *mini, t_cmd *cmd)
{
	t_env	*env;
	int		i;

	i = 0;
	env = mini->h_env;
	if (!arg_exists(cmd->args, i))
		return (print_sorted_env(mini), SUCCESS);
	while (arg_exists(cmd->args, i))
	{
		process_args(mini, cmd, &env, &i);
		i++;
	}
	return (get_sig()->status);
}

/**
 * @brief Processes the arguments of the export command.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param cmd Pointer to the command structure.
 * @param env Double pointer to the environment variable structure.
 * @param i Pointer to the index of the current argument.
 */
static void	process_args(t_mini *mini, t_cmd *cmd, t_env **env, int *i)
{
	char	*name;
	char	*value;

	name = malloc(sizeof(char) * BUFF_SIZE);
	if (!name)
		error_manager(mini, MALLOC, NULL, NULL);
	get_env_name(name, cmd->args[*i]);
	if (!is_valid_env(name) || !ft_strcmp(name, "_"))
	{
		if (!is_valid_env(name))
		{
			ft_memdel(name);
			export_err(mini, EINVAL, cmd->args[*i]);
		}
		(*i)++;
		return ;
	}
	get_env_value(mini, &value, name, cmd->args[*i]);
	if (!set_env(mini, env, name, value))
		env_add(mini, name, value);
	ft_memdel(name);
	ft_memdel(value);
}

/**
 * @brief Adds a new environment variable to the list.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param name Pointer to the name of the new environment variable.
 * @param value Pointer to the value of the new environment variable.
 * @return {int} - Returns SUCCESS if the environment variable
 * was added successfully, ERROR otherwise.
 */
static int	env_add(t_mini *mini, char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		error_manager(mini, MALLOC, NULL, NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (clean_export(new, name, value, FALSE),
			error_manager(mini, MALLOC, NULL, NULL), ERROR);
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
			return (clean_export(new, name, value, TRUE),
				error_manager(mini, MALLOC, NULL, NULL), ERROR);
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (add_env_to_list(mini, new));
}

/**
 * @brief Adds a new environment variable to the list.
 * 
 * @param mini Pointer to the mini shell structure.
 * @param new Pointer to the new environment variable to be added.
 * @return {int} - Returns SUCCESS if the environment
 * variable was added successfully.
 */
static int	add_env_to_list(t_mini *mini, t_env *new)
{
	t_env	*tmp;

	if (mini->h_env == NULL)
	{
		mini->env = new;
		mini->h_env = new;
	}
	else
	{
		tmp = mini->h_env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}
