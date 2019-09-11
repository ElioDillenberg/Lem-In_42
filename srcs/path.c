/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:42:34 by thallot           #+#    #+#             */
/*   Updated: 2019/09/10 13:13:09 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

void	set_max_path(t_env *env)
{
	int start;
	int end;
	int j;

	end = 0;
	start = 0;
	j = 0;
	while (j < env->nt_rm[1])
	{
		if (env->tu_tab[0][j])
			start++;
		j++;
	}
	j = 0;
	while (j < env->nt_rm[1])
	{
		if (env->tu_tab[env->nt_rm[1] - 1][j])
			end++;
		j++;
	}
	env->max_path = start > end ? end : start;
	if (env->nt_rm[0] < env->max_path)
		env->max_path = env->nt_rm[0];
}

int		get_opti_path(t_env *env, t_path *path)
{
	int		nb_path;
	int		size;
	int		rounds;
	int		mod;

	size = 0;
	nb_path = 0;
	while (path)
	{
		size += path->len;
		nb_path++;
		path = path->next_path;
	}
	mod = (size + env->nt_rm[0]) % nb_path;
	rounds = ((size + env->nt_rm[0]) / nb_path) - 1;
	rounds += mod > 0 ? 1 : 0;
	if (env->total_rounds == 0)
		env->total_rounds = rounds;
	if (env->total_rounds >= rounds && get_strt_ants(env, rounds, mod))
	{
		env->total_rounds = rounds;
		return (env->cr_path);
	}
	return (env->cr_path == 1 ? 0 : 1);
}
