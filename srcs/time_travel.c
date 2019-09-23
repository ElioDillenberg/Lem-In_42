/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_travel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:48:46 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/18 10:03:37 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#define I intz[0]
#define J intz[1]
#define K intz[2]

static void	clean_tt(t_env *env, int apply)
{
	int i;

	i = 0;
	while (++i < env->nt_rm[1])
	{	
		if (env->rm_tab[i]->dfs_tt && apply)
			env->rm_tab[i]->dfs = env->rm_tab[i]->dfs_tt;
		env->rm_tab[i]->dfs_tt = 0;
		if (env->rm_tab[i]->path_tt && apply)
			env->rm_tab[i]->path = 1;
		env->rm_tab[i]->path_tt = 0;
		if (env->rm_tab[i]->parent_tt > 0 && apply)
			env->rm_tab[i]->parent = env->rm_tab[i]->parent_tt;
		env->rm_tab[i]->parent_tt = -1;
	}
}

static int	delete_room_path_tt(t_env *env)
{
	t_room	*room;

	room = *env->rm_lst_path_tt;
	*env->rm_lst_path_tt = (*env->rm_lst_path_tt)->next;
	ft_roomdelone(&room);
	return (0);
}

static int	path_visited(t_env *env, int *intz, int dfs_tt)
{
	int ret;

	if (env->tu_tab[J][get_index(env, J, env->rm_tab[J]->parent_tt)].status == 1)
	{
		if (env->tu_tab[K][get_index(env, K, J)].status == -1)
		{
			env->rm_tab[K]->parent_tt = J;
			env->rm_tab[K]->path_tt = 1;
			if ((ret = add_room_tt_ret(env, intz, dfs_tt, -1)) > -2)
				return (ret);
		}
	}
	else
	{
		if (env->tu_tab[K][get_index(env, K, J)].status == -1)
		{
			if (ft_better_way(env, J) == 0)
			{
				env->rm_tab[K]->parent_tt = J;
				env->rm_tab[K]->path_tt = 1;
				if (add_room_tt(env, intz, -1) == -1)
					return (-1);
			}
		}
		else
		{
			env->rm_tab[K]->parent_tt = J;
			env->rm_tab[K]->path_tt = 1;
			if ((ret = add_room_tt_ret(env, intz, dfs_tt, 1)) > -2)
				return (ret);
		}
	}
	return (-2);
}

static int	found_path_tt(t_env *env, int *intz, int dfs_tt)
{
	int	ret;

	if (env->rm_tab[J]->visited)
	{
		if ((ret = path_visited(env, intz, dfs_tt)) > -2)
			return (ret);
	}
	else
	{
		env->rm_tab[K]->parent_tt = J;
		env->rm_tab[K]->path_tt = 1;
		if ((ret = add_room_tt_ret(env, intz, dfs_tt, 1)) > -2)
			return (ret);
	}
	return (-2);
}

int			bfs_time_travel(t_env *env, int index, int dfs_tt)
{
	int		ret;
	int		intz[3];

	if (add_room_path_tt(env, env->rm_tab[index]) == -1)
		return (-1);
	env->rm_tab[index]->dfs_tt = dfs_tt;
	while (*env->rm_lst_path_tt && !(*env->rm_lst_path_tt)->end)
	{
		I = -1;
		J = (*env->rm_lst_path_tt)->index;
		delete_room_path_tt(env);
		while (env->tu_tab[J][++I].exist)
		{
			if (env->tu_tab[J][I].status == 1
			&& !env->rm_tab[env->tu_tab[J][I].index]->path
			&& !env->rm_tab[env->tu_tab[J][I].index]->path_tt
			&& env->tu_tab[J][I].index != 0)
			{
				K = env->tu_tab[J][I].index;
				if ((ret = found_path_tt(env, intz, dfs_tt)) > -2)
				{
					ft_roomdel(env->rm_lst_path_tt, 0);
					clean_tt(env, 1);
					return (ret);
				}
			}
		}
	}
	clean_tt(env, 0);
	return (ft_roomdel(env->rm_lst_path_tt, 0));
}
