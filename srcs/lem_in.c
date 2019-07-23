/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/23 19:28:58 by edillenb         ###   ########.fr       */
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
*/

int		set_room_data(char *line, t_room *room, int *command)
{
	if (*command == 1)
	{
		t_room->start = true;
		*command = 0;
	}
	else
		t_room->start = false;
	if (*command == 2)
	{
		t_room->end = true;
		*command = 0;
	}
	else
		t_room->end = false;
	t_room->ant_here = false;
	t_room->ant = 0;
	if (get_room(line, room) == -1)
		return (-1);
}

int			add_room(char *line, t_room **head, int *command)
{
	t_room *new_room;
	t_room *last;

	last = *head;
	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		return (free_room_lst(head));
	if (!(set_room_data(t_room, line, command)))
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

	if (argc > 1 || parsing(&room_lst, &nb_ants) == -1)
		return (free_room_lst(&room_lst, 1));
	if (check_input(room_lst, nb_ants) == -1)
		return (free_room_lst(&room_lst, 1));
}
