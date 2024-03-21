/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/03/20 18:17:13 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	exit_error_numeric(t_mini *mini)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(mini->cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	mini->sig.status = 2;
	ft_exit(mini, 1);
}

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

void	mini_exit(t_mini *mini)
{
	size_t		i;
	int			pbm;
	long long	code;

	pbm = 0;
	i = 1;
	mini->sig.status = 0;
	if (!mini->cmd->args[1])
		ft_exit(mini, 1);
	exit_arg(mini);
	while (mini->cmd->args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		mini->sig.status = 1;
	}
	else
	{
		code = ft_atoi_exit(mini->cmd->args[1], 0, &pbm);
		if (pbm == 1)
			exit_error_numeric(mini);
		mini->sig.status = code % 256;
	}
	ft_exit(mini, 1);
}
