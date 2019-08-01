/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 11:24:48 by thallot           #+#    #+#             */
/*   Updated: 2019/07/30 11:24:49 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int		free_room_lst(t_room **head, int opt)
{
	t_room *cr;
	t_room *next;

	cr = *head;
	next = NULL;
	while (cr != NULL)
	{
		next = cr->next;
		ft_memdel((void**)&(cr->name));
		ft_memdel((void**)&cr);
		cr = next;
	}
	if (opt == 1)
		write(2, "ERROR\n", 6);
	return (-1);
}

int		free_all(t_env *env, int opt)
{
  if (env->to_print)
    ft_memdel((void**)&(env)->to_print);
	ft_memdel((void**)&(env)->path);
  free_int_tab(env, env->nt_rm[1]);
	if (env->nb_path)
		ft_roomdel(env->rm_lst_path);
	ft_memdel((void **)&(env)->rm_lst_path);
  ft_roomdel(env->rm_lst);
  ft_memdel((void **)&(env)->rm_lst);
  ft_memdel((void **)&(env)->rm_tab);
  ft_memdel((void **)&env);
	if (opt == 1)
		write(2, "ERROR\n", 6);
	return (-1);
}

void	free_int_tab(t_env *env, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_memdel((void **)&(env)->tu_tab[i]);
		i++;
	}
	ft_memdel((void **)&(env)->tu_tab);
}

void ft_roomdel(t_room **room)
{
	if (!room)
		return ;
	while ((*room)->next)
    ft_roomdel(&(*room)->next);
	ft_roomdelone(room);
}

void	ft_roomdelone(t_room **room)
{
	if (!room)
		return ;
  ft_memdel((void **)&(*room)->name);
  ft_memdel((void **)room);
	(*room) = NULL;
}
