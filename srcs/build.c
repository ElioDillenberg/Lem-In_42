/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:55:53 by thallot           #+#    #+#             */
/*   Updated: 2019/09/11 12:01:38 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int				print_rm_tab(t_env *env)
{
	int i;

	i = 0;
	while (i < env->nt_rm[1])
	{
		ft_printf("ROOM: %s\n", env->rm_tab[i]->name);
		ft_printf("start = %d\n", env->rm_tab[i]->start);
		ft_printf("end = %d\n", env->rm_tab[i]->end);
		i++;
	}
	return (0);
}

// static t_room	*set_first(t_room *cr, t_room *prev,
// 		t_room *first, t_room **rm_lst)
// {
// 	first = cr;
// 	prev->next = cr->next;
// 	cr = cr->next;
// 	first->next = *rm_lst;
// 	*rm_lst = first;
// 	return (cr);
// }

// static t_room	*set_last(t_room *cr, t_room *last)
// {
// 	cr->next = last;
// 	last->next = NULL;
// 	return (cr);
// }

// static	t_room	*find_last(t_room *cr, t_room *prev, t_room **rm_lst)
// {
// 	if (cr != *rm_lst)
// 		prev->next = cr->next;
// 	else
// 		*rm_lst = cr->next;
// 	return (prev);
// }

// static int		set_lst(t_room *prev, t_room *last,
// 		t_room *first, t_room **rm_lst)
// {
// 	t_room	*cr;
// 	int		len;

// 	len = 0;
// 	cr = *rm_lst;
// 	while (cr != NULL)
// 	{
// 		ft_printf("1\n");
// 		if (cr->start && cr != *rm_lst && ++len)
// 		{
// 			ft_printf("2.1\n");
// 			cr = set_first(cr, prev, first, rm_lst);
// 			ft_printf("2.2\n");
// 		}
// 		else if (++len)
// 		{
// 			ft_printf("3.0\n");
// 			if (cr->end && cr->next != NULL && --len)
// 			{
// 				last = cr;
// 				ft_printf("3.1\n");
// 				prev = find_last(cr, prev, rm_lst);
// 				ft_printf("3.2\n");
// 			}
// 			else if (cr->next == NULL && !cr->end)
// 			{
// 				ft_printf("cr : %s\n", cr->name);
// 				ft_printf("last : %s\n", cr->name);
// 				print_lst(rm_lst);
// 				ft_printf("3.3\n");
// 				cr = set_last(cr, last);
// 				ft_printf("3.4\n");
// 			}
// 			else
// 				prev = cr;
// 			cr = cr->next;
// 		}
// 	}
// 	return (len);
// }

void			swap_room(t_env *env, int i, int j)
{
	t_room	*tmp;

	tmp = env->rm_tab[i];
	env->rm_tab[i] = env->rm_tab[j];
	env->rm_tab[j] = tmp;
}

// void			swap_room(t_env *env, int i, int j)
// {
// 	t_room tmp;

// 	tmp.ant = env->rm_tab[i]->ant;
// 	tmp.dfs = env->rm_tab[i]->dfs;
// 	tmp.end = env->rm_tab[i]->end;
// 	tmp.index = env->rm_tab[i]->index;
// 	tmp.name = env->rm_tab[i]->name;
// 	tmp.next = env->rm_tab[i]->next;
// 	tmp.parent = env->rm_tab[i]->parent;
// 	tmp.path = env->rm_tab[i]->path;
// 	tmp.start = env->rm_tab[i]->start;
// 	tmp.visited = env->rm_tab[i]->visited;
// 	tmp.x = env->rm_tab[i]->x;
// 	tmp.y = env->rm_tab[i]->y;
// 	env->rm_tab[i]->ant = env->rm_tab[j]->ant;
// 	env->rm_tab[i]->dfs = env->rm_tab[j]->dfs;
// 	env->rm_tab[i]->end = env->rm_tab[j]->end;
// 	tmp.index = env->rm_tab[i]->index;
// 	tmp.name = env->rm_tab[i]->name;
// 	tmp.next = env->rm_tab[i]->next;
// 	tmp.parent = env->rm_tab[i]->parent;
// 	tmp.path = env->rm_tab[i]->path;
// 	tmp.start = env->rm_tab[i]->start;
// 	tmp.visited = env->rm_tab[i]->visited;
// 	tmp.x = env->rm_tab[i]->x;
// 	tmp.y = env->rm_tab[i]->y;
// }

void			set_room_tab(t_env *env)
{
	int 	i;

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

// int				build_room_tab(t_room **rm_lst, t_room ***rm_tab)
int				build_room_tab(t_env *env)
{
	t_room	*prev;
	t_room	*first;
	t_room	*last;

	first = NULL;
	prev = NULL;
	last = NULL;
	ft_printf("build_room_tab\n");
	env->nt_rm[1] = set_nb_room(env);
	ft_printf("env->nt_rm[1] == %d\n", env->nt_rm[1]);
	// len = set_lst(prev, last, first, rm_lst);
	if (get_room_tab(env, env->nt_rm[1]) == -1)
		return (-1);
	ft_printf("printing rm_tab\n");
	print_rm_tab(env);
	set_room_tab(env);
	ft_printf("printing rm_tab after set_room_tab\n");
	print_rm_tab(env);
	return (0);
}
