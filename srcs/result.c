/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:30:01 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/25 10:32:35 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>

int			set_ant_start(t_path *cr, int *rounds_cr, int *mod_cr, t_env *env)
{
	int to_send;
	int total_ants;

	total_ants = env->nt_rm[0];
	while (cr != NULL)
	{
		if ((to_send = *rounds_cr - cr->len + 1) <= 0)
			return (0);
		if (total_ants >= to_send)
		{
			cr->strt_ants = to_send;
			total_ants -= to_send;
		}
		else
		{
			cr->strt_ants = total_ants;
			total_ants = 0;
		}
		if (*mod_cr > 0 && (*mod_cr)--)
			cr->strt_ants++;
		cr = cr->next_path;
	}
	return (1);
}

static int	print_round(t_env *env, t_path *cr, int *no_space)
{
	*no_space == 0 ? *no_space = 1 : write(1, " ", 1);
	if (ft_printf("L%d-%s", cr->ant, env->rm_tab[cr->index]->name) == -1)
		return (-1);
	if (cr->next_room == NULL)
		env->ants_end++;
	else
		cr->next_room->ant = cr->ant;
	cr->ant = 0;
	return (1);
}

static int	print_result(t_path *cr, t_env *env, int no_space)
{
	t_path	*head;

	while (cr != NULL)
	{
		head = cr;
		cr = cr->tail_path;
		while (cr->prev_room != NULL)
		{
			if (cr->ant)
				if (!(print_round(env, cr, &no_space)))
					return (-1);
			if ((cr->prev_room->len && env->ants_end < env->nt_rm[0]
			&& env->next_ant <= env->nt_rm[0] && head->strt_ants > 0)
			|| (env->lf_path == 1 && cr->prev_room->len
			&& env->ants_end < env->nt_rm[0] && env->next_ant <= env->nt_rm[0]))
			{
				cr->ant = env->next_ant++;
				head->strt_ants--;
			}
			cr = cr->prev_room;
		}
		cr = cr->next_path;
	}
	return (1);
}

static int	one_round(t_env *env, t_path *cr)
{
	write(1, "\n", 1);
	while (env->nt_rm[0] >= env->next_ant)
	{
		if (ft_printf("L%d-%s", env->next_ant,
			env->rm_tab[cr->next_room->index]->name) == -1)
			return (-1);
		if (env->next_ant != 0 && env->next_ant != env->nt_rm[0])
			write(1, " ", 1);
		env->next_ant++;
	}
	write(1, "\n", 1);
	env->round = 1;
	return (1);
}

int			result(t_env *env)
{
	t_path	*cr;
	int		no_space;

	cr = NULL;
	cr = env->path_lst[env->cr_path];
	if (cr->len == 1)
	{
		one_round(env, cr);
		return (1);
	}
	while (env->ants_end < env->nt_rm[0])
	{
		cr = env->path_lst[env->cr_path];
		env->round++;
		no_space = 0;
		if (!(print_result(cr, env, no_space)))
			return (-1);
		write(1, "\n", 1);
	}
	env->round--;
	return (0);
}
