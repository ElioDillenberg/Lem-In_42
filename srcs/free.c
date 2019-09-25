/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 11:24:48 by thallot           #+#    #+#             */
/*   Updated: 2019/09/11 19:00:07 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int		free_room_lst(t_room **head)
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
	return (-1);
}

void	free_tu_tab(t_env *env)
{
	int i;

	i = -1;
	while (env->tu_tab && ++i < env->nt_rm[1])
		ft_memdel((void**)&(env)->tu_tab[i]);
	ft_memdel((void**)&env->tu_tab);
}

int		free_all(t_env *env, int ret)
{
	int i;

	i = -1;
	if (env->to_print)
		ft_memdel((void**)&(env)->to_print);
	if (env->opt_file_path)
		ft_memdel((void**)&(env)->opt_file_path);
	if (env->max_path)
		ft_roomdel(env->rm_lst_path, 0);
	ft_memdel((void**)&(env)->map);
	free_tu_tab(env);
	ft_path_lst_del(&(env->path_lst[0]));
	ft_path_lst_del(&(env->path_lst[1]));
	ft_memdel((void**)&(env)->path_lst);
	ft_roomdel(env->rm_lst, 0);
	ft_memdel((void **)&(env)->rm_lst_path);
	ft_memdel((void **)&(env)->rm_lst_path_tt);
	ft_memdel((void **)&(env)->parse);
	ft_memdel((void **)&(env)->rm_lst);
	ft_memdel((void **)&(env)->rm_tab);
	ft_memdel((void **)&env);
	return (ret);
}

void	ft_pathdel(t_path **path)
{
	t_path	*cr;
	t_path	*nxt_room;

	if (!path)
		return ;
	cr = *path;
	while (cr->next_room)
	{
		nxt_room = cr->next_room;
		ft_memdel((void**)&cr);
		cr = nxt_room;
	}
	ft_memdel((void**)&cr);
}

void	ft_path_lst_del(t_path **path_lst)
{
	t_path	*cr;
	t_path	*nxt_path;

	if (!*path_lst)
		return ;
	cr = *path_lst;
	while (cr->next_path)
	{
		nxt_path = cr->next_path;
		ft_pathdel(&cr);
		cr = nxt_path;
	}
	ft_pathdel(&cr);
}
