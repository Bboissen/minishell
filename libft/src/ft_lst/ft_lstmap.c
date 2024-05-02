/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talibabtou <talibabtou@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:17:48 by gdumas            #+#    #+#             */
/*   Updated: 2024/05/02 10:10:00 by talibabtou       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates the list 'lst' and applies the function 'f' to the content
 * of each element. Creates a new list resulting of the successive applications
 * of the function 'f'. The 'del' function is used to delete the content of an
 * element if needed.
 * 
 * @param lst The beginning of the list.
 * @param f The function to apply to the content of each element.
 * @param del The function to delete the content of an element if needed.
 * @return {t_list *} The new list. NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_obj;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_obj = ft_lstnew(content);
		if (!new_obj)
		{
			free(content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_obj);
		lst = lst->next;
	}
	return (new_lst);
}
