/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:12:59 by bboissen          #+#    #+#             */
/*   Updated: 2023/11/15 12:01:19 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*buff;

	if (lst)
	{
		buff = lst;
		while (buff != NULL)
		{
			if (lst->content && f)
				(f)(buff->content);
			buff = buff->next;
		}
	}
}
