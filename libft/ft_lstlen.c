/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:01:24 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 20:07:40 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_lstlen(t_list **alst)
{
	t_list	*current;
	size_t	len;

	current = *alst;
	len = 0;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}
