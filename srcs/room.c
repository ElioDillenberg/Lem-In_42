/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:06:30 by thallot           #+#    #+#             */
/*   Updated: 2019/09/11 18:39:54 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void set_dad(t_env *env, int i, int idx)
{
	int j;

	j = 0;
	ft_printf("OLD DAD of ROOM [%s] : [%s]\n", env->rm_tab[i]->name, env->rm_tab[env->rm_tab[i]->dad[0]]->name);
	while (env->rm_tab[i]->dad[j] != -1 && j < env->rm_tab[i]->nb_dad && env->rm_tab[i]->dad[j] != idx)
		j++;
	env->rm_tab[i]->dad[j] = idx;
	ft_printf("NEW DAD of ROOM [%s] : [%s] (j : %d)\n", env->rm_tab[i]->name, env->rm_tab[env->rm_tab[i]->dad[j]]->name, j);
}

/*
** This function parses the input found in line
** It then activates flags within the node depending on found type ->
*/

int		set_room_data(char *line, t_room *room, int *start_end)
{
	if (start_end[0] == 1)
	{
		room->start = true;
		start_end[0] = 2;
	}
	else
		room->start = false;
	if (start_end[1] == 1)
	{
		room->end = true;
		start_end[1] = 2;
	}
	else
		room->end = false;
	room->ant = 0;
	room->parent = -1;
	room->visited = false;
	room->path = 0;
	room->nb_dad = 0;
	room->next = NULL;
	if (get_room(line, room) == -1)
		return (-1);
	return (0);
}

/*
** One way to optimize parsing here would be to add room at the beginning of
** the list and not at the end.
*/

int		add_room(char *line, t_room **head, int *command)
{
	t_room	*new_room;
	t_room	*last;

	last = *head;
	if (!(new_room = (t_room*)ft_memalloc(sizeof(t_room))))
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

int		ft_roomdel(t_room **room, int ret)
{
	if (!(*room))
		return (0);
	while ((*room)->next)
		ft_roomdel(&((*room)->next), 0);
	ft_roomdelone(room);
	return (ret);
}

void	ft_roomdelone(t_room **room)
{
	if (!room)
		return ;
	ft_memdel((void **)&((*room)->name));
	ft_memdel((void **)&((*room)->dad));
	ft_memdel((void **)room);
	(*room) = NULL;
}
