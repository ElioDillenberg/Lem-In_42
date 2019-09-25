/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_travel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:48:46 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/25 12:00:04 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#define I intz[0]
#define J intz[1]
#define K intz[2]

static int	get_out(t_env *env, int *intz, int dfs_tt)
{
	int		ret;

	if (env->tu_tab[K][get_index(env, K, J)].status == -1)
	{
		if (ft_better_way(env, J) == 0)
		{
			set_dad(env, K, J);
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
	return (-2);
}

static int	path_visited(t_env *env, int *intz, int dfs_tt)
{
	int ret;

	if (env->tu_tab[J][get_index(env, J, env->rm_tab[J]->parent_tt)].status
			== 1)
	{
		if (env->tu_tab[K][get_index(env, K, J)].status == -1)
		{
			set_dad(env, K, J);
			env->rm_tab[K]->parent_tt = J;
			env->rm_tab[K]->path_tt = 1;
			if ((ret = add_room_tt_ret(env, intz, dfs_tt, -1)) > -2)
				return (ret);
		}
	}
	else if (!env->rm_tab[K]->path)
		if ((ret = get_out(env, intz, dfs_tt)) > -2)
			return (ret);
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
	else if (!env->rm_tab[env->tu_tab[J][I].index]->path)
	{
		env->rm_tab[K]->parent_tt = J;
		env->rm_tab[K]->path_tt = 1;
		if ((ret = add_room_tt_ret(env, intz, dfs_tt, 1)) > -2)
			return (ret);
	}
	return (-2);
}

static int	bfs_tt_loop(t_env *env, int dfs_tt, int *intz)
{
	int		ret;

	if (env->tu_tab[J][I].status == 1
			&& !env->rm_tab[env->tu_tab[J][I].index]->path_tt
			&& env->tu_tab[J][I].index != 0)
	{
		K = env->tu_tab[J][I].index;
		if ((ret = found_path_tt(env, intz, dfs_tt)) > -2)
		{
			set_dad(env, J, K);
			ft_roomdel(env->rm_lst_path_tt, 0);
			clean_tt(env, 1);
			return (ret);
		}
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
			if ((ret = bfs_tt_loop(env, dfs_tt, intz)) > -2)
				return (ret);
	}
	clean_tt(env, 0);
	return (ft_roomdel(env->rm_lst_path_tt, 0));
}
