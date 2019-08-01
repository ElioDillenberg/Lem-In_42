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
	room->parent = -1;
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

t_env *init_env(t_env *env)
{
	int j;

	j = 0;
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
			return (NULL);
	if (!(env->rm_lst = (t_room **)ft_memalloc(sizeof(t_room *))))
			return (NULL);
	if (!(env->rm_lst_path = (t_room **)ft_memalloc(sizeof(t_room *))))
			return (NULL);
	if (!(env->path = ft_strnew(0)))
			return (NULL);
	env->rm_tab = NULL;
	env->nb_path = 0;
	return (env);
}

int			main(int argc, char **argv)
{
	t_env *env;
	int to_find;

	to_find = 1;
	(void)argv;
	env = NULL;
	if (argc > 1)
		return (-1);
	if (!(env = init_env(env)))
		return (-1);
	if ((env->ret = parsing(env)) == -1)
		return (free_all(env, -1));
	//view_tunnel_by_name(env);
	ft_printf("\n\n");
	set_max_path(env);
	ft_printf("MAX NBR OF PATH: %d\n", env->max_path);
	if (env->max_path)
	{
		ft_bfs(env);
		get_path(env);
	}

	//path_finder(env);
//	if (check_input(room_lst, nb_ants) == -1)
//		return (free_room_lst(&room_lst, 1));
	return (free_all(env, 0));
}
