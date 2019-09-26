/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:54:33 by thallot           #+#    #+#             */
/*   Updated: 2019/09/26 11:28:45 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void		set_dad(t_env *env, int i, int idx)
{
	int j;

	j = 0;
	if (env->rm_tab[i]->dad[0] == -1)
		env->rm_tab[i]->dad[0] = idx;
	else
	{
		while (j < env->rm_tab[i]->nb_dad - 1
			&& env->rm_tab[i]->dad[j] != -1 && env->rm_tab[i]->dad[j] != idx)
			j++;
		env->rm_tab[i]->dad[j] = idx;
	}
}

void		reset_dad(t_env *env)
{
	int j;
	int i;

	i = 0;
	while (i < env->nt_rm[1])
	{
		j = 0;
		while (j < env->rm_tab[i]->nb_dad)
		{
			env->rm_tab[i]->dad[j] = -1;
			j++;
		}
		i++;
	}
}

int			set_daddy(t_env *env)
{
	int i;
	int	j;
	int nbr_co;

	i = 0;
	while (i < env->nt_rm[1])
	{
		j = 0;
		nbr_co = 0;
		while (j < env->nt_rm[1])
		{
			if (env->tu_tab[i][j].exist)
				nbr_co++;
			j++;
		}
		if (!(env->rm_tab[i]->dad = (int *)ft_memalloc(sizeof(int) * nbr_co)))
			return (-1);
		env->rm_tab[i]->nb_dad = nbr_co;
		while (nbr_co--)
			env->rm_tab[i]->dad[nbr_co] = -1;
		i++;
	}
	return (0);
}
