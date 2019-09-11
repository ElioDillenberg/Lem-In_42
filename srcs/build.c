/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:55:53 by thallot           #+#    #+#             */
/*   Updated: 2019/09/11 12:01:38 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static t_room	*set_first(t_room *cr, t_room *prev,
		t_room *first, t_room **rm_lst)
{
	first = cr;
	prev->next = cr->next;
	cr = cr->next;
	first->next = *rm_lst;
	*rm_lst = first;
	return (cr);
}

static t_room	*set_last(t_room *cr, t_room *last)
{
	cr->next = last;
	last->next = NULL;
	return (cr);
}

static	t_room	*find_last(t_room *cr, t_room *prev, t_room **rm_lst)
{
	if (cr != *rm_lst)
		prev->next = cr->next;
	else
		*rm_lst = cr->next;
	return (prev);
}

static int		set_lst(t_room *prev, t_room *last,
		t_room *first, t_room **rm_lst)
{
	t_room	*cr;
	int		len;

	len = 0;
	cr = *rm_lst;
	while (cr != NULL)
	{
		if (cr->start && cr != *rm_lst && ++len)
			cr = set_first(cr, prev, first, rm_lst);
		else if (++len)
		{
			if (cr->end && cr->next != NULL && --len)
			{
				last = cr;
				prev = find_last(cr, prev, rm_lst);
			}
			else if (cr->next == NULL && !cr->end)
				cr = set_last(cr, last);
			else
				prev = cr;
			cr = cr->next;
		}
	}
	return (len);
}

int				build_room_tab(t_room **rm_lst, t_room ***rm_tab)
{
	t_room	*prev;
	t_room	*first;
	t_room	*last;
	int		len;

	first = NULL;
	prev = NULL;
	last = NULL;
	len = set_lst(prev, last, first, rm_lst);
	if (!(*rm_tab = get_room_tab(rm_tab, rm_lst, len)))
		return (-1);
	return (len);
}
