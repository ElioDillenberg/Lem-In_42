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
	while (++i < env->nt_rm[1])
	{
		if (env->tu_tab[index][i].status == 1 && !env->rm_tab[i]->path && i)
			if (env->tu_tab[i][index].status != -1)
				return (1);
	}
	return (0);
}

static int	path_bfs(t_env *env, int i, int idx)
{
	int	ret;

	if (env->rm_tab[idx]->parent != -1 && env->rm_tab[idx]->visited == true)
	{
		// ft_printf("Starting TIME_travel here : %s\n", env->rm_tab[idx]->name);
		if ((ret = bfs_time_travel(env, idx, env->rm_tab[idx]->dfs + 1)) == -1)
			return (-1);
		// ft_printf("time_travel_ret = %d, which is room : %s\n", ret, env->rm_tab[ret]->name);
		// ft_printf("rm_tab[idx]->path = %d\n", env->rm_tab[idx]->path);
		if (ret)
		{
			env->rm_tab[ret]->dfs = env->rm_tab[idx]->dfs + 1;
			// ft_printf("on va add la room au BFS sa mere la teps\n");
			if ((ret = add_room_bfs(env, ret)) > -2)
			{
				// ft_printf("ret de add_room_bfs dans path_bfs = %d\n", ret);
				return (ret);
			}
			// ft_printf("add_room s'est bien passe visiblement, faut break\n");
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
			{
				ft_printf("ret dans bfs loop = %d\n", ret);
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
