/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:14:47 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 19:40:04 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstputstr(t_list **alst)
{
	t_list	*current;

	if (!alst)
		return ;
	current = *alst;
	while (current != 0)
	{
		ft_putstr(current->content);
		current = current->next;
	}
}
