/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_travel_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:14:45 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/25 11:34:02 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#define I intz[0]
#define J intz[1]
#define K intz[2]

void	clean_tt(t_env *env, int apply)
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

int		delete_room_path_tt(t_env *env)
{
	t_room	*room;

	room = *env->rm_lst_path_tt;
	*env->rm_lst_path_tt = (*env->rm_lst_path_tt)->next;
	ft_roomdelone(&room);
	return (0);
}
