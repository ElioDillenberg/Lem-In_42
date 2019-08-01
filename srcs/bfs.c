/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 12:35:39 by thallot           #+#    #+#             */
/*   Updated: 2019/08/01 12:35:41 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

/* Ajout d'une room dans env->rm_lst_path*/

int			add_room_path(t_env *env, t_room *room)
{
	t_room 	*new_room;
	t_room 	*last;

	last = *(env->rm_lst_path);
	if (!(new_room = (t_room*)ft_memalloc(sizeof(t_room))))
		return (0);
	new_room->name = ft_strdup(room->name);
	new_room->index = room->index;
  new_room->parent = room->parent;
  new_room->end = room->end;
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

/* Ajout de la premiere dans env->rm_lst_path*/

int			delete_room_path(t_env *env)
{
	t_room 	*room;

	room = (*env->rm_lst_path);
	(*env->rm_lst_path) = (*env->rm_lst_path)->next;
	ft_roomdelone(&room);
	return (0);
}

void print_lst(t_env *env)
{
  t_room *room;

  room = (*env->rm_lst_path);
  ft_printf("Room : ");
  while (room)
  {
    ft_printf("%s ", room->name);
    room = room->next;
  }
  ft_printf("\n");
}


/* Parcours de graphe en largeur, cf BFS. Pour chaque enfant,
son parent est spécifié dans room->parent
*/
void ft_bfs(t_env *env)
{
  int i;
  int index;

  add_room_path(env, env->rm_tab[0]);
  (*env->rm_lst_path)->path = 1;
  while (!(*env->rm_lst_path)->end)
  {
    i = 0;
    index = (*env->rm_lst_path)->index;
    delete_room_path(env);
    while (i < env->nt_rm[1])
    {
      if (env->tu_tab[i][index] == 1 && env->rm_tab[i]->path == 0 && i != 0)
      {
        env->rm_tab[i]->path = 1;
        env->rm_tab[i]->parent = index;
        add_room_path(env, env->rm_tab[i]);
      }
      i++;
    }
    if ((*env->rm_lst_path)->end)
      env->nb_path++;
  }
}

/* Parcours la graphe en commencant par la fin, et en remontant par le parent de chaque rooms
le path est un char *, où les rooms sont renseignées par leur noms ( a changer par leur index), et delimieter par un espace

Il faudrait supprimer les chemins entre les parents et enfants du path, pour relancer bfs et trouver un nouveau path
*/

void get_path(t_env *env)
{
	int pere;
  int index;

  index = env->nt_rm[1] - 1;
  pere = env->rm_tab[index]->parent;
  env->path = ft_joinfree(env->path, env->rm_tab[index]->name);
  env->path = ft_joinfree(env->path, " ");
	while (env->rm_tab[index]->parent != -1)
	{
		pere = env->rm_tab[index]->parent;
    index = env->rm_tab[pere]->index;
		env->path = ft_joinfree(env->path, env->rm_tab[index]->name);
    if (env->rm_tab[index]->parent != -1)
      env->path = ft_joinfree(env->path, " ");
	}
  env->path = ft_strrev(env->path);
  ft_printf("PATH : [%s]\n", env->path);
}
