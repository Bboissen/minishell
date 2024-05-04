/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:42:56 by talibabtou        #+#    #+#             */
/*   Updated: 2024/05/03 15:40:47 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_err(t_mini *mini, int error, char *arg)
{
	t_sig	*sig;

	sig = get_sig();
	(void) error;
	sig->status = 1;
	ft_printfd(STDERR_FILENO, "%s: `%s': \
not a valid identifier\n", mini->name, arg);
	return (sig->status);
}

void	cd_err(t_mini *mini, int err, char *arg)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = err;
	if (err == errno)
		ft_printfd(STDERR_FILENO, "%s: %s: %s\n",
			mini->name, arg, strerror(err));
	if (err == ERROR)
		ft_printfd(STDERR_FILENO, "%s: cd: \
too many arguments\n", mini->name);
	else if (err == MISSING)
		ft_printfd(STDERR_FILENO, "%s: cd: \
$HOME not set\n", mini->name);
	else if (err == DIRECTORY)
		ft_printfd(STDERR_FILENO, "cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n");
	else
		error_manager(mini, MALLOC, NULL, NULL);
}
