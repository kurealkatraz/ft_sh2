/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgras <mgras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/06 22:32:07 by mgras             #+#    #+#             */
/*   Updated: 2015/03/22 15:18:48 by mgras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin_list;
	t_list	*list;
	t_list	*new;

	list = (t_list *)malloc(sizeof(t_list));
	begin_list = list;
	if (list && (*f) && lst)
	{
		list = (*f)(lst);
		begin_list = list;
		while (lst->next)
		{
			lst = lst->next;
			new = (t_list *)malloc(sizeof(t_list));
			if (new)
			{
				new = (*f)(lst);
				list->next = new;
				list = list->next;
			}
			else
				return (NULL);
		}
	}
	return (begin_list);
}
