/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_travel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:48:46 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/10 13:48:48 by edillenb         ###   ########.fr       */
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
	if (*(env->rm_lst_path) == NULL)
	{
		*(env->rm_lst_path) = new_room;
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

int         bfs_time_travel(t_env *env, int index, int dfs_tt)
{
    int     i;
    int     indextt;

    if (add_room_path_tt(env, env->rm_tab[index]) == -1)
        return (-1);
    while (*env->rm_lst_path_tt && !(*env->rm_lst_path_tt)->end)
    {
        i = -1;
        indextt = (*env->rm_lst_path_tt)->index;
        delete_room_path_tt(env);
        while (++i < env->nt_rm[1])
        {
            if (env->tu_tab[indextt][i] == 1 && !env->rm_tab[i]->path && i)
			{
				if (env->rm_tab[indextt]->parent != -1 && env->rm_tab[env->rm_tab[indextt]->parent]->visited == false && env->rm_tab[indextt]->visited == true)
				{
					if (env->tu_tab[i][indextt] == -1)
					{
                        env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs - 1;
						env->rm_tab[i]->path = 1;
						env->rm_tab[i]->parent = indextt;
						if (add_room_path_tt(env, env->rm_tab[i]) == -1)
							return (-1);
                        if (env->rm_tab[i]->dfs == dfs_tt)
                        {
                            ft_roomdel(env->rm_lst_path_tt);
                            return (i);
                        }
					}
				}
				else if (env->rm_tab[indextt]->parent != -1 && env->rm_tab[env->rm_tab[indextt]->parent]->visited == true && env->rm_tab[indextt]->visited == true)
				{
					if (env->tu_tab[i][indextt] == -1)
					{
						if (ft_better_way(env, indextt) == 0)
						{
							env->rm_tab[i]->path = 1;
							env->rm_tab[i]->parent = indextt;
                            env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs - 1;
							if (add_room_path_tt(env, env->rm_tab[i]) == -1)
								return (-1);
						}
					}
					else
					{
						env->rm_tab[i]->path = 1;
						env->rm_tab[i]->parent = index;
                        env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs + 1;
						if (add_room_path_tt(env, env->rm_tab[i]) == -1)
							return (-1);
						if (env->rm_tab[i]->dfs == dfs_tt)
                        {
                            ft_roomdel(env->rm_lst_path_tt);
                            return (i);
                        }
					}
				}
				else
				{
					env->rm_tab[i]->path = 1;
					env->rm_tab[i]->parent = indextt;
                    env->rm_tab[i]->dfs = env->rm_tab[indextt]->dfs + 1;
					if (add_room_path_tt(env, env->rm_tab[i]) == -1)
						return (-1);
					if (env->rm_tab[i]->dfs == dfs_tt)
                    {
                        ft_roomdel(env->rm_lst_path_tt);
                        return (i);
                    }
				}
			}
        }
    }
    if (!(*env->rm_lst_path_tt))
        ft_printf("on est arrives a la fin!\n");
    else if ((*env->rm_lst_path_tt)->end)
        ft_printf("on est arrives a end!\n");
    ft_roomdel(env->rm_lst_path_tt);
    return (0);
}