/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:51:43 by thallot           #+#    #+#             */
/*   Updated: 2019/09/24 19:37:57 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#define I intz[0]
#define J intz[1]
#define K intz[2]

int		add_room_path_tt(t_env *env, t_room *room)
{
	t_room	*new_room;
	t_room	*last;

	last = *(env->rm_lst_path_tt);
	if (!(new_room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (-1);
	if (!(new_room->name = ft_strdup(room->name)))
	{
		ft_memdel((void**)&new_room);
		return (-1);
	}
	new_room->index = room->index;
	new_room->parent = room->parent;
	new_room->end = room->end;
	new_room->visited = 0;
	if (*(env->rm_lst_path_tt) == NULL)
	{
		*(env->rm_lst_path_tt) = new_room;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_room;
	return (0);
}

int		add_room_path(t_env *env, t_room *room)
{
	t_room	*new_room;
	t_room	*last;

	last = *(env->rm_lst_path);
	if (!(new_room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (-1);
	if (!(new_room->name = ft_strdup(room->name)))
	{
		ft_memdel((void**)&new_room);
		return (-1);
	}
	new_room->index = room->index;
	new_room->parent = room->parent;
	new_room->end = room->end;
	new_room->visited = 0;
	if (*(env->rm_lst_path) == NULL)
	{
		*(env->rm_lst_path) = new_room;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_room;
	return (0);
}

int		add_room_tt(t_env *env, int *intz, int opt)
{
	if (opt == 1)
		env->rm_tab[K]->dfs = env->rm_tab[J]->dfs + 1;
	else
		env->rm_tab[K]->dfs = env->rm_tab[J]->dfs - 1;
	env->rm_tab[K]->path_tt = 1;
	env->rm_tab[K]->parent_tt = J;
	if (add_room_path_tt(env, env->rm_tab[K]) == -1)
		return (-1);
	return (0);
}

int		add_room_tt_ret(t_env *env, int *intz, int dfs_tt, int opt)
{
	if (add_room_tt(env, intz, opt) == -1)
		return (-1);
	if (env->rm_tab[K]->dfs == dfs_tt
		&& (env->rm_tab[K]->visited == false || env->rm_tab[K]->end))
		return (ft_roomdel(env->rm_lst_path_tt, K));
	return (-2);
}

int		add_room_bfs(t_env *env, int ret)
{
	if (add_room_path(env, env->rm_tab[ret]) == -1)
		return (-1);
	if (env->rm_tab[ret]->end)
	{
		env->nb_path++;
		return (0);
	}
	return (-2);
}
