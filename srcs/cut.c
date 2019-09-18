/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:01:20 by thallot           #+#    #+#             */
/*   Updated: 2019/09/18 10:01:03 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

/*
** This function will parse env->tu_tab to check wether
** or not we have found a "-1"
** if one has been found, it means we need to cut all the
*/

void	cut_and_reset(t_env *env, int opt, int visited)
{
	int i;
	int j;

	i = -1;
	while (++i < env->nt_rm[1])
	{
		j = -1;
		if (visited == true)
			env->rm_tab[i]->visited = false;
		while (++j < env->nt_rm[1])
		{
			if (env->tu_tab[i][j].status == -2)
				env->tu_tab[i][j].status = 0;
			else if (env->tu_tab[i][j].status == -1)
				env->tu_tab[i][j].status = 1;
		}
	}
	env->tu_cut = 0;
	env->nb_path = 0;
	if (opt == 1)
	{
		ft_path_lst_del(&(env->path_lst[env->cr_path]));
		env->path_lst[env->cr_path] = NULL;
	}
}

void	reset_path_room(t_env *env, int opt)
{
	int i;

	i = 0;
	while (i < env->nt_rm[1])
	{
		if (opt == 1)
			env->rm_tab[i]->dfs = 0;
		env->rm_tab[i]->path = 0;
		env->rm_tab[i]->parent = -1;
		i++;
	}
}
