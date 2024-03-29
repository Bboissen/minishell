/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:47:09 by bboissen          #+#    #+#             */
/*   Updated: 2024/01/25 14:52:29 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void	clr_content(t_list *lst, int list_type)
{
	if (list_type == 1)
	{
		if (((t_exec *)(lst->cont))->args)
			free_array(((t_exec *)((lst)->cont))->args);
		free((t_exec *)(lst->cont));
	}
	if (list_type == 2)
		free((t_word *)(lst->cont));
}

void	ft_lstdelone(t_list *lst, void (*del)(t_list *, int), int type)
{
	if (lst)
	{
		if ((lst)->cont && del)
			(del)(lst, type);
		free(lst);
		lst = NULL;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(t_list *, int), int type)
{
	t_list	*buff;

	while (*lst != NULL)
	{
		buff = (*lst)->next;
		ft_lstdelone(*lst, del, type);
		(*lst) = buff;
	}
	free(*lst);
	*lst = NULL;
}

void	free_array(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

char	**clear_cmd(char **args, t_list **cmd, int mode)
{
	void	(*fun_ptr)(t_list*, int);

	fun_ptr = clr_content;
	if (args && mode == -1)
		free_array(args);
	ft_lstclear(cmd, fun_ptr, 2);
	return (NULL);
}
