/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:48:22 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/25 10:24:48 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

static int	add_path_index(t_path **path, int index, t_env *env)
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

static int	add_path_lst(t_env *env, t_path *path)
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

static void	set_data_get_path(t_env *env, int *parent, int *index, int *save)
{
	int idx_index;
	int idx_save;

	*save = *index;
	env->rm_tab[*index]->visited = true;
	*parent = env->rm_tab[*index]->parent;
	if (*parent != -1)
	{
		*index = env->rm_tab[*parent]->index;
		idx_index = get_index(env, *index, *save);
		idx_save = get_index(env, *save, *index);
		env->tu_tab[*index][idx_index].status =
		env->tu_tab[*save][idx_save].status == -1 ? -2 : -1;
	}
	else
	{
		*index = 0;
		env->tu_tab[0][*save].status =
		env->tu_tab[*save][0].status == -1 ? -2 : -1;
	}
}

static void	loop_get_path(t_env *env, int index, int save)
{
	if (env->tu_tab[save][get_index(env, save, index)].status == -1)
	{
		env->tu_tab[index][get_index(env, index, save)].status = -2;
		env->tu_tab[save][get_index(env, save, index)].status = -2;
		env->tu_cut = 1;
	}
	else
		env->tu_tab[index][get_index(env, index, save)].status = -1;
}

int			get_path(t_env *env)
{
	int		parent;
	int		index;
	int		save;
	t_path	*path;
	int		j;

	path = NULL;
	index = env->nt_rm[1] - 1;
	j = 0;
	while (env->rm_tab[index]->dad[j] != -1 && j < env->rm_tab[index]->nb_dad)
		j++;
	j--;
	parent = env->rm_tab[index]->dad[j];
	if (add_path_index(&path, index, env) == -1)
		return (-1);
	while (env->rm_tab[index]->dad[j] != -1)
	{
		if (!env->rm_tab[env->rm_tab[index]->dad[j]]->end)
			env->rm_tab[index]->dad[j] = -1;
		set_data_get_path(env, &parent, &index, &save);
		loop_get_path(env, index, save);
		if (add_path_index(&path, index, env) == -1)
			return (-1);
	}
	return (add_path_lst(env, path));
}
