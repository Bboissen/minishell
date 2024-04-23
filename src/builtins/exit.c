/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:05:10 by gdumas            #+#    #+#             */
/*   Updated: 2024/04/23 18:34:09 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmdsize(t_cmd *h_cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = h_cmd;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/*static int	ft_atoi_exit(const char *str, int i, int *pbm)
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

static void	exit_arg(t_mini *mini)
{
	char	*arg;
	int		i;
	t_sig	*sig;

	sig = get_sig();
	arg = mini->cmd->args[0];
	if (arg && (arg[0] == '-' || arg[0] == '+'))
	{
		ft_printfd(2, "%s: exit: %s: numeric argument \
required\n", mini->name, arg);
		sig->status = 2;
	}
	i = 0;
	while (arg && arg[i])
	{
		if (!isdigit(arg[i]))
		{
			ft_printfd(2, "%s: exit: %s: numeric argument \
required\n", mini->name, arg);
			sig->status = 2;
		}
		i++;
	}
}

int	mini_exit(t_mini *mini)
{
	int			pbm;
	t_sig		*sig;

	(void)mini;
	sig = get_sig();
	if (mini->cmd->args && mini->cmd->args[0])
	{
		exit_arg(mini);
		if (mini->cmd->args[1])
			return (ft_printfd(2, "exit\n%s: exit: too many arguments\n",
					mini->name), sig->status = 1);
		pbm = 0;
		sig->status = (ft_atoi_exit(mini->cmd->args[1], 0, &pbm)) % 256;
		if (pbm == 1)
			return (ft_printfd(2, "%s: exit: %s: numeric argument required\n",
					mini->name, mini->cmd->args[1]), sig->status = 2);
	}
	if (cmdsize(mini->h_cmd) == 1)
		sig->exit = 1;
	return (sig->status);
}*/

int	mini_exit(t_mini *mini)
{
	t_sig	*sig;
	int		narg;

	narg = ft_atoi(mini->cmd->args[0]);
	sig = get_sig();
	if (mini->cmd->args)
	{
		if (!ft_isdigit(narg))
		{
			ft_printfd(2, "%s: exit: %s: numeric argument required\n",
				mini->name, mini->cmd->args[0]);
			sig->status = 2;
		}
		else
			sig->status = ft_atoi(mini->cmd->args[0]) % 256;
	}
	if (mini->cmd->args && mini->cmd->args[1])
	{
		ft_printfd(2, "exit\n%s: exit: too many arguments\n", mini->name);
		sig->status = 1;
	}
	if (cmdsize(mini->h_cmd) == 1)
		sig->exit = 1;
	return (sig->status);
}
