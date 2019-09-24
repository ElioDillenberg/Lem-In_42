/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:55:53 by thallot           #+#    #+#             */
/*   Updated: 2019/09/24 19:36:49 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void			swap_room(t_env *env, int i, int j)
{
	t_room	*tmp;

	tmp = env->rm_tab[i];
	env->rm_tab[i] = env->rm_tab[j];
	env->rm_tab[j] = tmp;
}

void			set_room_tab(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nt_rm[1])
	{
		if (env->rm_tab[i]->start && i != 0)
			swap_room(env, 0, i);
		if (env->rm_tab[i]->end && i != env->nt_rm[1] - 1)
		{
			swap_room(env, env->nt_rm[1] - 1, i);
			if (env->rm_tab[i]->start)
				swap_room(env, 0, i);
		}
		env->rm_tab[i]->index = i;
		i++;
	}
}

int				set_nb_room(t_env *env)
{
	t_room	*cr;
	int		i;

	i = 0;
	cr = *env->rm_lst;
	while (cr)
	{
		i++;
		cr = cr->next;
	}
	return (i);
}

int				build_room_tab(t_env *env)
{
	t_room	*prev;
	t_room	*first;
	t_room	*last;

	first = NULL;
	prev = NULL;
	last = NULL;
	env->nt_rm[1] = set_nb_room(env);
	if (get_room_tab(env, env->nt_rm[1]) == -1)
		return (-1);
	set_room_tab(env);
	return (0);
}
