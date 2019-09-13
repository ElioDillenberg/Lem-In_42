/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 12:35:39 by thallot           #+#    #+#             */
/*   Updated: 2019/09/11 18:18:11 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void		reset_path_room(t_env *env, int opt)
{
	int i;

	i = 0;
	while (i < env->nt_rm[1])
	{
		if (opt == 1)
			env->rm_tab[i]->dfs = 0;
		env->rm_tab[i]->path = 0;
		env->rm_tab[i]->path_tt = 0;
		env->rm_tab[i]->parent = -1;
		env->rm_tab[i]->parent_tt = -1;
		i++;
	}
}

int			add_room_path(t_env *env, t_room *room)
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

int			delete_room_path(t_env *env)
{
	t_room	*room;

	room = *env->rm_lst_path;
	*env->rm_lst_path = (*env->rm_lst_path)->next;
	ft_roomdelone(&room);
	return (0);
}

int			add_path_index(t_path **path, int index, t_env *env)
{
	t_path	*new;

	if (!(new = (t_path*)ft_memalloc(sizeof(t_path))))
		return (-1);
	new->index = index;
	if (*path == NULL)
	{
		*path = new;
		new->nb = env->nb_path;
		new->tail_path = new;
	}
	else
	{
		new->next_room = *path;
		*path = new;
		new->len = new->next_room->len + 1;
		new->nb = new->next_room->nb;
		new->next_room->nb = 0;
		new->next_room->len = 0;
		new->next_room->prev_room = new;
		new->tail_path = new->next_room->tail_path;
		new->next_room->tail_path = NULL;
	}
	return (0);
}

int			add_path_lst(t_env *env, t_path *path)
{
	t_path	*cr;
	int		i;

	i = 1;
	cr = env->path_lst[env->cr_path];
	if (env->path_lst[env->cr_path] == NULL)
	{
		path->nb = i;
		env->path_lst[env->cr_path] = path;
	}
	else
	{
		i++;
		while (cr->next_path != NULL)
		{
			cr = cr->next_path;
			i++;
		}
		cr->next_path = path;
		path->nb = i;
	}
	return (0);
}

int			ft_better_way(t_env *env, int index)
{
	int	i;

	i = -1;
	while (++i < env->nt_rm[1])
	{
		if (env->tu_tab[index][i] == 1 && !env->rm_tab[i]->path && i)
			if (env->tu_tab[i][index] != -1)
				return (1);
	}
	return (0);
}

static int	add_room_bfs(t_env *env, int ret)
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

static int	found_path_bfs(t_env *env, int i, int idx)
{
	int	ret;

	if (env->rm_tab[idx]->parent != -1 && env->rm_tab[idx]->visited == true)
	{
		if ((ret = bfs_time_travel(env, idx, env->rm_tab[idx]->dfs + 1)) == -1)
			return (-1);
		if (ret)
		{
			env->rm_tab[ret]->dfs = env->rm_tab[idx]->dfs + 1;
			if ((ret = add_room_bfs(env, ret)) > -2)
				return (ret);
		}
	}
	else
	{
		env->rm_tab[i]->dfs = env->rm_tab[idx]->dfs + 1;
		env->rm_tab[i]->path = 1;
		env->rm_tab[i]->parent = idx;
		if ((ret = add_room_bfs(env, i)) > -2)
			return (ret);
	}
	return (-2);
}

int			bfs_loop(t_env *env)
{
	int i;
	int	index;
	int	ret;

	i = -1;
	index = (*env->rm_lst_path)->index;
	delete_room_path(env);
	while (++i < env->nt_rm[1])
	{
		if (env->tu_tab[index][i] == 1 && !env->rm_tab[i]->path && i)
		{
			if ((ret = found_path_bfs(env, i, index)) > -2)
				return (ret);
		}
	}
	if (!(*env->rm_lst_path) || (*env->rm_lst_path)->end)
	{
		env->nb_path += env->lf_path;
		if (!(*env->rm_lst_path))
		{
			env->finish = 1;
			return (1);
		}
	}
	return (-2);
}

int			ft_bfs(t_env *env, int start)
{
	int	ret;

	if (add_room_path(env, env->rm_tab[start]) == -1)
		return (-1);
	while (*env->rm_lst_path && !(*env->rm_lst_path)->end)
		if ((ret = bfs_loop(env)) > -2)
			return (ret);
	return (0);
}

static void	set_data_get_path(t_env *env, int *parent, int *index, int *save)
{
	*save = *index;
	env->rm_tab[*index]->visited = true;
	*parent = env->rm_tab[*index]->parent;
	*index = env->rm_tab[*parent]->index;
	env->tu_tab[*index][*save] = env->tu_tab[*save][*index] == -1 ? -2 : -1;
}

int			get_path(t_env *env)
{
	int		parent;
	int		index;
	int		save;
	t_path	*path;

	path = NULL;
	index = env->nt_rm[1] - 1;
	parent = env->rm_tab[index]->parent;
	if (add_path_index(&path, index, env) == -1)
		return (-1);
	while (env->rm_tab[index]->parent != -1)
	{
		set_data_get_path(env, &parent, &index, &save);
		if (env->tu_tab[save][index] == -1)
		{
			env->tu_tab[index][save] = -2;
			env->tu_tab[save][index] = -2;
			env->tu_cut = 1;
		}
		else
			env->tu_tab[index][save] = -1;
		if (add_path_index(&path, index, env) == -1)
			return (-1);
	}
	return (add_path_lst(env, path));
}
