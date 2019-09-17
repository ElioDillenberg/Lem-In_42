/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_travel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:48:46 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/11 15:16:34 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#define I intz[0]
#define J intz[1]

static int	add_room_path_tt(t_env *env, t_room *room)
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

static int	delete_room_path_tt(t_env *env)
{
	t_room	*room;

	room = *env->rm_lst_path_tt;
	*env->rm_lst_path_tt = (*env->rm_lst_path_tt)->next;
	ft_roomdelone(&room);
	return (0);
}

static int	add_room_tt(t_env *env, int *intz, int opt)
{
	if (opt == 1)
		env->rm_tab[I]->dfs = env->rm_tab[J]->dfs + 1;
	else
		env->rm_tab[I]->dfs = env->rm_tab[J]->dfs - 1;
	env->rm_tab[I]->path = 1;
	env->rm_tab[I]->parent = J;
	if (add_room_path_tt(env, env->rm_tab[I]) == -1)
		return (-1);
	return (0);
}

static int	add_room_tt_ret(t_env *env, int *intz, int dfs_tt, int opt)
{
	if (add_room_tt(env, intz, opt) == -1)
		return (-1);
	if (env->rm_tab[I]->dfs == dfs_tt)
		return (ft_roomdel(env->rm_lst_path_tt, I));
	return (-2);
}

static int	path_visited(t_env *env, int *intz, int dfs_tt)
{
	int ret;

	if (env->rm_tab[env->rm_tab[J]->parent]->visited == false)
	{
		if (env->tu_tab[I][J].status == -1)
		{
			if ((ret = add_room_tt_ret(env, intz, dfs_tt, -1)) > -2)
				return (ret);
		}
	}
	else
	{
		if (env->tu_tab[I][J].status == -1)
		{
			if (ft_better_way(env, J) == 0)
			{
				if (add_room_tt(env, intz, -1) == -1)
					return (-1);
			}
		}
		else if ((ret = add_room_tt_ret(env, intz, dfs_tt, 1)) > -2)
			return (ret);
	}
	return (-2);
}

static int	found_path_tt(t_env *env, int *intz, int dfs_tt)
{
	int	ret;

	if (env->rm_tab[J]->parent != -1 && env->rm_tab[J]->visited)
	{
		if ((ret = path_visited(env, intz, dfs_tt)) > -2)
			return (ret);
	}
	else if ((ret = add_room_tt_ret(env, intz, dfs_tt, 1)) > -2)
		return (ret);
	return (-2);
}

int			bfs_time_travel(t_env *env, int index, int dfs_tt)
{
	int		ret;
	int		intz[2];

	if (add_room_path_tt(env, env->rm_tab[index]) == -1)
		return (-1);
	while (*env->rm_lst_path_tt && !(*env->rm_lst_path_tt)->end)
	{
		I = -1;
		J = (*env->rm_lst_path_tt)->index;
		delete_room_path_tt(env);
		while (++I < env->nt_rm[1])
		{
			if (env->tu_tab[J][I].status == 1 && !env->rm_tab[I]->path && I)
			{
				if ((ret = found_path_tt(env, intz, dfs_tt)) > -2)
					return (ret);
			}
		}
	}
	return (ft_roomdel(env->rm_lst_path_tt, 0));
}
