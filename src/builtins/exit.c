/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/03 10:15:14 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if an argument exists at a given index.
 * 
 * @param args The array of arguments.
 * @param index The index to check.
 * @return {int} 1 if an argument exists at the given index, FALSE otherwise.
 */
int	arg_exists(char **args, int index)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (FALSE);
	while (args[i] != NULL)
		i++;
	return (i > index);
}

/**
 * @brief Convert a string to an integer, with error checking for exit command.
 * 
 * @param str The string to convert.
 * @param i The starting index in the string.
 * @param overflow Pointer to an integer to store any error.
 * @return {int} The converted integer.
 */
static int	ft_atoi_exit(const char *str, int i, int *overflow)
{
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sum > LLONG_MAX / 10
			|| (sum == LLONG_MAX / 10 && str[i] - '0' > LLONG_MAX % 10))
		{
			*overflow = 1;
			break ;
		}
		sum = (sum * 10) + (str[i] - 48);
		i++;
	}
	return (sum * neg);
}

/**
 * @brief Validate if the argument is numeric.
 * 
 * @param mini The mini structure.
 * @param sig The sig structure.
 * @param overflow The error flag.
 * @return {int} ERROR if the argument is not numeric, SUCCESS otherwise.
 */
static int	validate_numeric_argument(t_mini *mini, t_cmd *cmd,
	t_sig *sig, int overflow)
{
	int	i;

	i = 0;
	if (cmd->args[0][i] == '-' || cmd->args[0][i] == '+'
		|| cmd->args[0][i] == ' ')
		i++;
	while (cmd->args[0][i])
	{
		if (!ft_isdigit(cmd->args[0][i++]) || overflow == 1)
		{
			ft_printfd(STDERR_FILENO,
				"%s: exit: %s: numeric argument required\n",
				mini->name, cmd->args[0]);
			sig->status = 2;
			return (ERROR);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Handle the exit command.
 * 
 * @param mini The mini structure.
 * @return {int} The status of the exit command.
 */
int	mini_exit(t_mini *mini, t_cmd *cmd)
{
	t_sig	*sig;
	int		narg;
	int		overflow;

	sig = get_sig();
	narg = 0;
	overflow = 0;
	if (cmd->args)
	{
		narg = ft_atoi_exit(cmd->args[0], 0, &overflow);
		if (validate_numeric_argument(mini, cmd, sig, overflow) == ERROR
			|| narg > INT_MAX || narg < INT_MIN)
		{
			sig->exit = TRUE;
			return (sig->status);
		}
		sig->status = narg % 256;
	}
	ft_printfd(STDERR_FILENO, "exit\n");
	if (cmd->args && arg_exists(cmd->args, 1))
	{
		ft_printfd(STDERR_FILENO,
			"%s: exit: too many arguments\n", mini->name);
		sig->status = ERROR;
	}
	sig->exit = TRUE;
	return (sig->status);
}
