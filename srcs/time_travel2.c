/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_travel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:48:46 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/16 11:10:46 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	add_room_path_tt(t_env *env, t_room *room)
{
	t_room	*new_room;
	t_room	*last;

	last = *(env->rm_lst_path_tt);
	if (!(new_room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (-1);
	if (!(new_room->name = ft_strdup(room->name)))
	{
		ft_memdel((void**)&new_room);
		return (-1);
	}
	new_room->index = room->index;
	new_room->parent = room->parent;
	new_room->end = room->end;
	new_room->visited = 0;
	if (*(env->rm_lst_path_tt) == NULL)
	{
		*(env->rm_lst_path_tt) = new_room;
		return (0);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_room;
	return (0);
}

static int	delete_room_path_tt(t_env *env)
{
	t_room	*room;

	room = *env->rm_lst_path_tt;
	*env->rm_lst_path_tt = (*env->rm_lst_path_tt)->next;
	ft_roomdelone(&room);
	return (0);
}

void		clean_tt(t_env *env, int apply)
{
	int i;

	i = 0;
	while (++i < env->nt_rm[1])
	{
		if (env->rm_tab[i]->path_tt && apply)
			env->rm_tab[i]->path = 1;
		env->rm_tab[i]->path_tt = 0;
		if (env->rm_tab[i]->parent_tt > 0 && apply)
			env->rm_tab[i]->parent = env->rm_tab[i]->parent_tt;
		env->rm_tab[i]->parent_tt = -1;
	}
}

/*
   void		apply_time_travel(t_env *env, int i, int index)
   {
   while (i != index)
   {
   env->rm_tab[i]->path = 1;
   env->rm_tab[i]->parent = env->rm_tab[i]->parent_tt;
   i = env->rm_tab[i]->parent;
   }
   }
   */

int         bfs_time_travel(t_env *env, int index, int dfs_tt)
{
	int     i;
	int     indextt;

	env->rm_tab[index]->parent_tt = env->rm_tab[index]->parent;
	env->rm_tab[index]->is_tt = 1;
	ft_printf("Time travel starting with room [%s]\n", env->rm_tab[index]->name);
	if (add_room_path_tt(env, env->rm_tab[index]) == -1)
		return (-1);
	// env->rm_tab[index]->path_tt = 1;
	while (*env->rm_lst_path_tt && !(*env->rm_lst_path_tt)->end)
	{
		i = 0;
		indextt = (*env->rm_lst_path_tt)->index;
		delete_room_path_tt(env);

		while (++i < env->nt_rm[1])
		{
			ft_printf("Room : %s ->path = %d et ->path_tt = %d ->visite %d -> parent %d ",
					env->rm_tab[i]->name, env->rm_tab[i]->path, env->rm_tab[i]->path_tt, env->rm_tab[i]->visited, env->rm_tab[i]->parent);
			if (env->rm_tab[i]->parent != -1)
				ft_printf("->Parent Name %s\n", env->rm_tab[env->rm_tab[i]->parent]->name);
			else
				ft_printf("\n");


			if (env->tu_tab[indextt][i] == 1 && !env->rm_tab[i]->path && !env->rm_tab[i]->path_tt)
			{
				ft_printf("On est rentré ici\n");
				ft_printf("indextt = %s and i = %s\n", env->rm_tab[indextt]->name, env->rm_tab[i]->name);
				if ((env->rm_tab[indextt]->parent_tt != -1 && env->rm_tab[env->rm_tab[indextt]->parent_tt]->visited == false && env->rm_tab[indextt]->visited == true)
				|| (env->tu_tab[indextt][env->rm_tab[indextt]->parent_tt] != -1 && env->rm_tab[env->rm_tab[indextt]->parent_tt]->visited == true && env->rm_tab[indextt]->visited == true))
				{

					ft_printf("SEG1.0\n");
					if (env->tu_tab[i][indextt] == -1)
					{
						ft_printf("SEG1\n");
						env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs - 1;
						env->rm_tab[i]->path_tt = 1;
						env->rm_tab[i]->parent_tt = indextt;
						ft_printf("i : %s / i->parent : %s\n", env->rm_tab[i]->name, env->rm_tab[env->rm_tab[i]->parent_tt]->name);
						env->rm_tab[i]->parent_tt = indextt;
						ft_printf("SEG1.1\n");
						if (add_room_path_tt(env, env->rm_tab[i]) == -1)
							return (-1);
						ft_printf("SEG1.2\n");
						if (env->rm_tab[i]->dfs == dfs_tt && env->rm_tab[i]->visited == false)
						{
							ft_printf("SORTIE_1\n");
							clean_tt(env, 1);
							return (ft_roomdel(env->rm_lst_path_tt, i));
						}
					}
					else
						ft_printf(" PAS A MOINS 1\n");
				}


				else if (env->rm_tab[env->rm_tab[indextt]->parent_tt]->visited == true && env->rm_tab[indextt]->visited == true)
				{
					ft_printf("SEG2\n");
					if (env->tu_tab[i][indextt] == -1)
					{
						ft_printf("NO BETTER WAY\n");
						if (ft_better_way(env, indextt) == 0)
						{
							env->rm_tab[i]->path_tt = 1;
							env->rm_tab[i]->parent_tt = indextt;
							env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs - 1;
							if (add_room_path_tt(env, env->rm_tab[i]) == -1)
								return (-1);
						}
					}
					else
					{
						ft_printf("BETTER WAY\n");
						env->rm_tab[i]->path_tt = 1;
						env->rm_tab[i]->parent_tt = indextt;
						env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs + 1;
						if (add_room_path_tt(env, env->rm_tab[i]) == -1)
							return (-1);
						if (env->rm_tab[i]->dfs == dfs_tt && env->rm_tab[i]->visited == false)
						{
							ft_printf("SORTIE_2\n");
							clean_tt(env, 1);
							return (ft_roomdel(env->rm_lst_path_tt, i));
						}
					}
				}
				else
				{
					ft_printf("SEG3\n");
					env->rm_tab[i]->path_tt = 1;
					env->rm_tab[i]->parent_tt = indextt;
					env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs + 1;
					if (add_room_path_tt(env, env->rm_tab[i]) == -1)
						return (-1);
					if (env->rm_tab[i]->dfs == dfs_tt  && env->rm_tab[i]->visited == false)
					{
						ft_printf("SORTIE_3\n");
						clean_tt(env, 1);
						return (ft_roomdel(env->rm_lst_path_tt, i));
					}
				}
			}
			ft_printf("LOOP room ");
		}
		ft_printf("LOOP rm_lst\n");
	}
	ft_printf("BEFORE CLEAN\n");
	clean_tt(env, 0);
	env->rm_tab[indextt]->path = 0;
	env->rm_tab[indextt]->parent = -1;
	ft_printf("END OF TT\n");
	return (ft_roomdel(env->rm_lst_path_tt, 0));
}
