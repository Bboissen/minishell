/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:42:56 by talibabtou        #+#    #+#             */
/*   Updated: 2024/05/01 17:02:25 by bboissen         ###   ########.fr       */
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

static void	cd_err_next(t_mini *mini, int err, char *arg)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = err;
	if (err == ERROR)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
Too many arguments\n", mini->name, arg);
	else if (err == MISSING)
		ft_printfd(STDERR_FILENO, "%s: cd: \
%d not set\n\n", mini->name, arg);
	else
		error_manager(mini, MALLOC, NULL, NULL);
}

void	cd_err(t_mini *mini, int err, char *arg)
{
	t_sig	*sig;

	sig = get_sig();
	sig->status = err;
	if (err == EACCES)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
Permission denied\n", mini->name, arg);
	else if (err == EIO)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
Input/output error\n", mini->name, arg);
	else if (err == ELOOP)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
Too many symbolic links encountered\n", mini->name, arg);
	else if (err == ENAMETOOLONG)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
Path is too long\n", mini->name, arg);
	else if (err == ENOENT)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
No such file or directory\n", mini->name, arg);
	else if (err == ENOTDIR)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
Not a directory\n", mini->name, arg);
	else if (err == EFAULT)
		ft_printfd(STDERR_FILENO, "%s: cd: %s: \
Bad address\n", mini->name, arg);
	else
		cd_err_next(mini, err, arg);
}
