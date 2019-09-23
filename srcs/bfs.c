/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 12:35:39 by thallot           #+#    #+#             */
/*   Updated: 2019/09/18 09:56:47 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void		delete_room_path(t_env *env)
{
	t_room	*room;

	room = *env->rm_lst_path;
	*env->rm_lst_path = (*env->rm_lst_path)->next;
	ft_roomdelone(&room);
}

int			ft_better_way(t_env *env, int index)
{
	int	i;

	i = -1;
	while (env->tu_tab[index][++i].exist)
	{
		if (env->tu_tab[index][i].status == 1 && !env->rm_tab[i]->path && env->tu_tab[index][i].index != 0)
			if (env->tu_tab[i][index].status != -1)
				return (1);
	}
	return (0);
}

static int	path_bfs(t_env *env, int i, int idx)
{
	int	ret;

	if (env->rm_tab[i]->visited == true && i != env->nt_rm[1] -1)
	{
		env->rm_tab[i]->parent_tt = idx;
		env->rm_tab[i]->path_tt = 1;
		env->rm_tab[i]->dfs_tt = env->rm_tab[idx]->dfs;
		// ft_printf("Time Travel dfs_tt = %d\n", env->rm_tab[idx]->dfs + 1);
		if ((ret = bfs_time_travel(env, i, env->rm_tab[i]->dfs)) == -1)
			return (-1);
		if (ret)
		{
			ft_printf("adding room %s after time travel\n", env->rm_tab[ret]->name);
			env->rm_tab[ret]->dfs = env->rm_tab[i]->dfs + 1;
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
	while (env->tu_tab[index][++i].exist)
	{
		if (env->tu_tab[index][i].status == 1
			&& !env->rm_tab[env->tu_tab[index][i].index]->path
			&& env->tu_tab[index][i].index != 0)
			if ((ret = path_bfs(env, env->tu_tab[index][i].index, index)) > -2)
				return (ret);
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
