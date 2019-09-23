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

	if (env->rm_tab[env->rm_tab[J]->parent_tt]->visited == false)
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

	// ft_printf("Found a possible tunnel towards %s\n", env->rm_tab[K]->name);
	if (env->rm_tab[J]->visited)
	{
		if ((ret = path_visited(env, intz, dfs_tt)) > -2)
			return (ret);
	}
	else
	{
		ft_printf("adding this room to TT : %s\n", env->rm_tab[K]->name);
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
	while (*env->rm_lst_path_tt && !(*env->rm_lst_path_tt)->end)
	{
		I = -1;
		J = (*env->rm_lst_path_tt)->index;
		// ft_printf("TT from %s\n", env->rm_tab[J]->name);
		delete_room_path_tt(env);
		while (++I < env->nt_rm[1])
		{
			// ft_printf("J = %s\n", env->rm_tab[J]->name);
			// ft_printf("I = %s\n", env->rm_tab[I]->name);
			if (env->tu_tab[J][I].status == 1
			&& !env->rm_tab[env->tu_tab[J][I].index]->path
			&& !env->rm_tab[env->tu_tab[J][I].index]->path_tt
			&& env->tu_tab[J][I].index != 0)
			{
				ft_printf("TT found path from : %s , to : %s\n",env->rm_tab[J]->name, env->rm_tab[env->tu_tab[J][I].index]->name);
				K = env->tu_tab[J][I].index;
				if ((ret = found_path_tt(env, intz, dfs_tt)) > -2)
				{
					// ft_printf("ret = %d\n", ret);
					ft_roomdel(env->rm_lst_path_tt, 0);
					clean_tt(env, 1);
					return (ret);
				}
			}
		}
		// ft_printf("END OF WHILE\n");
	}
	// env->rm_tab[index]->path = 0;
	// env->rm_tab[index]->parent = -1;
	clean_tt(env, 0);
	return (ft_roomdel(env->rm_lst_path_tt, 0));
}
