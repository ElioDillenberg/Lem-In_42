/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:33:00 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:05:52 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*current;

	current = NULL;
	while (lst != NULL)
	{
		if (!current)
		{
			if (!(current = f(lst)))
				return (NULL);
			head = current;
		}
		else
		{
			if (!(current->next = f(lst)))
				return (NULL);
			current = current->next;
		}
		lst = lst->next;
	}
	return (head);
}
