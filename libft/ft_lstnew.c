/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 01:02:41 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 16:58:03 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_elem;

	if (!(new_elem = (t_list*)malloc(sizeof(*new_elem))))
		return (NULL);
	if (!content)
	{
		new_elem->content_size = 0;
		new_elem->content = NULL;
	}
	else
	{
		if (!(new_elem->content = (void *)malloc(sizeof(content_size))))
		{
			free(new_elem);
			return (NULL);
		}
		ft_memcpy(new_elem->content, content, content_size);
		new_elem->content_size = content_size;
	}
	new_elem->next = NULL;
	return (new_elem);
}
