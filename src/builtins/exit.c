/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/29 18:05:07 by gdumas           ###   ########.fr       */
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
	int			j;
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	j = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		sum = (sum * 10) + (str[i] - 48);
		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && neg == -1) && (str[i] == '9')))
			*overflow = 1;
		i++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*overflow = 1;
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
static int	validate_numeric_argument(t_mini *mini, t_sig *sig, int overflow)
{
	int	i;

	i = 0;
	if (mini->cmd->args[0][i] == '-' || mini->cmd->args[0][i] == '+')
		i++;
	while (mini->cmd->args[0][i])
	{
		if (!ft_isdigit(mini->cmd->args[0][i++]) || overflow == 1)
		{
			ft_printfd(STDERR_FILENO,
				"%s: exit: %s: numeric argument required\n",
				mini->name, mini->cmd->args[0]);
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
int	mini_exit(t_mini *mini)
{
	t_sig	*sig;
	int		narg;
	int		overflow;

	sig = get_sig();
	narg = 0;
	if (mini->cmd->args)
	{
		narg = ft_atoi_exit(mini->cmd->args[0], 0, &overflow);
		if (validate_numeric_argument(mini, sig, overflow) == ERROR)
			return (sig->status);
		sig->status = narg % 256;
	}
	sig->exit = TRUE;
	ft_printfd(STDERR_FILENO, "exit\n");
	if (mini->cmd->args && arg_exists(mini->cmd->args, 1))
	{
		ft_printfd(STDERR_FILENO,
			"%s: exit: too many arguments\n", mini->name);
		sig->status = ERROR;
		sig->exit = FALSE;
	}
	return (sig->status);
}
