/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/29 19:02:03 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

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

t_env *init_env(t_env *env)
{
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
			return (NULL);
	if (!(env->rm_lst = (t_room **)ft_memalloc(sizeof(t_room *))))
			return (NULL);
	env->rm_tab = NULL;
	return (env);
}

int			main(int argc, char **argv)
{
	t_env *env;

	(void)argv;
	env = NULL;
	if (argc > 1)
		return (-1);
	if (!(env = init_env(env)))
		return (-1);
	if ((env->ret = parsing(env)) == -1)
		return (free_all(env, -1));
	find_path(env, 0);
//	ft_printf("[%s]\n", (*env->rm_lst)->next->name);
//	if (check_input(room_lst, nb_ants) == -1)
//		return (free_room_lst(&room_lst, 1));
	return (free_all(env, 0));
}
