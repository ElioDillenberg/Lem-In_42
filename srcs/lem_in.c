/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/22 19:31:40 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>

int		free_room_lst(t_room **head, int opt)
{
	t_room *cr;
	t_room *next;

	cr = *head;
	next = NULL;
	while (cr != NULL)
	{
		next = cr->next;
		ft_memdel((void**)&(cr->name));
		ft_memdel((void**)&cr);
		cr = next;
	}
	if (opt == 1)
		write(2, "ERROR\n", 6);
	return (-1);
}

/*
** This function parses the input found in line
** It then activates flags within the node depending on found type ->
** QUESTION: how do I know this is a start or end? Maybe send an int table 
** that would be modified while parsing when I find a start or end instruction ?
*/

int		set_room_data(t_room *room, char *line, int opt)
{
	t_room->name = line;
	if (opt == 1)
		t_room->start = true;
	else
		t_room->start = false;
	if (opt == 2)
		t_room->end = true;
	else
		t_room->end = false;
	t_room->ant_here = false;
	t_room->ant = 0;
	x = 
}

int			add_room(t_room **head, char *line)
{
	t_room *new_room;
	t_room *last;

	last = *head;
	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		return (free_room_lst(head));
	if (!(set_room_data(t_room, char *line)))
		return (free_room_lst(head));
	if (*head == NULL)
	{
		*head = new_room;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_room;
}

int			main(void)
{
	t_room	*room_lst = NULL;
	int		*ant_tab = NULL;
	size_t	nb_ants;

	if (argc > 1 || parsing(&room_lst, &ant_tab, &nb_ants) == -1)
		return (free_room_lst(&room_lst, 1));
}
