/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/28 20:29:07 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
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
		room->start = true;
		*command = 0;
	}
	else
		room->start = false;
	if (*command == 2)
	{
		room->end = true;
		*command = 0;
	}
	else
		room->end = false;
	room->ant_here = false;
	room->ant = 0;
	room->next = NULL;
	if (get_room(line, room) == -1)
		return (-1);
	return (0);
}

int			add_room(char *line, t_room **head, int *command)
{
	t_room 	*new_room;
	t_room 	*last;

	last = *head;
	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		return (free_room_lst(head, -1));
	if (set_room_data(line, new_room, command) == -1)
		return (free_room_lst(head, -1));
	if (*head == NULL)
	{
		*head = new_room;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_room;
	return (0);
}

int			main(int argc, char **argv)
{
	t_room	*rm_lst = NULL;
	t_room	*rm_tab = NULL;
	int		nt_rm[2];
	int		**tu_tab;

	(void)argv;
	if (argc > 1)
		return (-1);
	if (parsing(&rm_lst, nt_rm, &rm_tab, &tu_tab) == -1)
		return (free_room_lst(&rm_lst, -1));
//	if (check_input(room_lst, nb_ants) == -1)
//		return (free_room_lst(&room_lst, 1));
	free(rm_tab);
	return (free_room_lst(&rm_lst, 0));
}
