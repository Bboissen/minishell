/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/27 18:26:29 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Convert a string to a long long integer, checking for potential errors.
 * @param {const char*} str - The string to convert.
 * @param {int} i - The starting index in the string.
 * @param {int*} pbm - Pointer to an integer to store the error status.
 * @return {long long} - Returns the converted integer.
 */
static long long	ft_atoi_exit(const char *str, int i, int *pbm)
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
			*pbm = 1;
		i++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*pbm = 1;
	return (sum * neg);
}

/**
 * Print an error message if the exit argument is not numeric.
 * @param {t_mini*} mini - The main structure of the shell.
 */
static void	exit_error_numeric(t_mini *mini)
{
	ft_printfd(2,
		"minishell: exit: '%s': numeric argument required\n",
		mini->cmd->args[1]);
	mini->sig.status = 2;
	clean_exit(mini, 1);
}

/**
 * Check the arguments of the exit command.
 * @param {t_mini*} mini - The main structure of the shell.
 */
static void	exit_arg(t_mini *mini)
{
	int		i;
	char	**args;

	i = 0;
	args = mini->cmd->args;
	if (args[i] == '-' || args[i] == '+')
		i++;
	while (args[i])
	{
		if (args[i] != '\f' && args[i] != '\t' && args[i] != '\r'
			&& args[i] != '\v' && args[i] != ' ')
		{
			if (args[i] < '0' || args[i] > '9')
				exit_error_numeric(mini);
		}
		i++;
	}
}

/**
 * Execute the exit command.
 * @param {t_mini*} mini - The main structure of the shell.
 */
void	mini_exit(t_mini *mini)
{
	size_t		i;
	int			pbm;
	long long	code;

	pbm = 0;
	i = 1;
	mini->sig.status = 0;
	if (!mini->cmd->args[1])
		clean_exit(mini, 1);
	exit_arg(mini);
	while (mini->cmd->args[i])
		i++;
	if (i > 2)
	{
		ft_printfd(2, "minishell: exit: too many arguments\n");
		mini->sig.status = 1;
	}
	else
	{
		code = ft_atoi_exit(mini->cmd->args[1], 0, &pbm);
		if (pbm == 1)
			exit_error_numeric(mini);
		mini->sig.status = code % 256;
	}
	clean_exit(mini, 1);
}
