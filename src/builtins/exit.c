/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/18 11:29:20 by gdumas           ###   ########.fr       */
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
/*static long long	ft_atoi_exit(const char *str, int i, int *pbm)
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
}*/

/**
 * Check the arguments of the exit command.
 * @param {t_mini*} mini - The main structure of the shell.
 */
/*static void	exit_arg(t_mini *mini)
{
	char	*arg;
	int		i;
	t_sig	*sig;

	sig = get_sig();
	arg = mini->cmd->args[1];
	if (arg && (arg[0] == '-' || arg[0] == '+'))
	{
		ft_printfd(2, "%s: exit: %s: numeric argument \
			required\n", mini->name, arg);
		sig->status = 2;
		return ;
	}
	i = 0;
	while (arg && arg[i])
	{
		if (!isdigit(arg[i]))
		{
			ft_printfd(2, "%s: exit: %s: numeric argument \
				required\n", mini->name, arg);
			sig->status = 2;
			return ;
		}
		i++;
	}
}*/

/**
 * Execute the exit command.
 * @param {t_mini*} mini - The main structure of the shell.
 */
int	mini_exit(t_mini *mini)
{
	/*int			pbm;
	long long	code;*/
	t_sig		*sig;

	(void)mini;
	sig = get_sig();
	/*if (!mini->cmd->args[1])
	{
		clean_exit(mini);
		sig->status = 0;
		sig->exit = 1;
	}
	exit_arg(mini);
	if (sig->status == 2)
		return (sig->status);
	if (mini->cmd->args[2])
		return (ft_printfd(2, "%s: exit: too many arguments\n",
				mini->name), sig->status = 1);
	pbm = 0;
	code = ft_atoi_exit(mini->cmd->args[1], 0, &pbm);
	if (pbm == 1)
		return (ft_printfd(2, "%s: exit: %s: numeric argument required\n",
				mini->name, mini->cmd->args[1]), sig->status = 2);
	sig->status = code % 256;*/
	sig->exit = 1;
	/*printf("%d\n", sig->exit);
	return (sig->status);*/
	return (0);
}
