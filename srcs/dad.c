/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:54:33 by thallot           #+#    #+#             */
/*   Updated: 2019/09/24 14:54:34 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void set_dad(t_env *env, int i, int idx)
{
	int j;

	j = 0;
	// ft_printf("OLD DAD of ROOM [%s] : [%s]\n", env->rm_tab[i]->name, env->rm_tab[env->rm_tab[i]->dad[0]]->name);
	while (env->rm_tab[i]->dad[j] != -1 && j < env->rm_tab[i]->nb_dad && env->rm_tab[i]->dad[j] != idx)
		j++;
	env->rm_tab[i]->dad[j] = idx;
	// ft_printf("NEW DAD of ROOM [%s] : [%s] (j : %d)\n", env->rm_tab[i]->name, env->rm_tab[env->rm_tab[i]->dad[j]]->name, j);
}

void reset_dad(t_env *env)
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

void		set_daddy(t_env *env)
{
	int i;
	int	j;
	int nbr_connexion;

	i = 0;
	while (i < env->nt_rm[1])
	{
		j = 0;
		nbr_connexion = 0;
		while (j < env->nt_rm[1])
		{
			if (env->tu_tab[i][j].exist && nbr_connexion++)
				;
			j++;
		}
		env->rm_tab[i]->dad = (int *)malloc(sizeof(int) * nbr_connexion);
		env->rm_tab[i]->nb_dad = nbr_connexion;
		while (nbr_connexion--)
			env->rm_tab[i]->dad[nbr_connexion] = -1;
		// ft_printf("\n");
		i++;
	}
}
