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

/*
Reset les parent et les path (variable qui definis si une case a ete explorée )
pour relancer bfs et trouver un nouveau Parcours
*/
void reset_path_room(t_env *env)
{
  int i;

  i = 0;
  while (i < env->nt_rm[1])
  {
    env->rm_tab[i]->path = 0;
    env->rm_tab[i]->parent = -1;
    i++;
  }
}

/*
Ajout d'une room dans env->rm_lst_path
*/

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

/*
Ajout de la premiere dans env->rm_lst_path
*/

int			delete_room_path(t_env *env)
{
	t_room 	*room;

	room = (*env->rm_lst_path);
	(*env->rm_lst_path) = (*env->rm_lst_path)->next;
	ft_roomdelone(&room);
	return (0);
}

/*
Parcours de graphe en largeur, cf BFS. Pour chaque enfant,
son parent est spécifié dans room->parent pour ensuite recreer le chemin
*/

void ft_bfs(t_env *env, int start)
{
  int i;
  int index;

  // ajout de la room start a la liste
  add_room_path(env, env->rm_tab[start]);
  // Parcours du graphe jusqu a trouver la room de sortie
  while ((*env->rm_lst_path) && !(*env->rm_lst_path)->end)
  {
    i = 0;
    // On prends l index de start et on la supprime de la liste
    index = (*env->rm_lst_path)->index;
    delete_room_path(env);
    while (i < env->nt_rm[1])
    {
      if (env->tu_tab[i][index] == 1 && env->rm_tab[i]->path == 0 && i != 0)
      {
        // Si une connection a ete trouve avec une autre room on renseigne son parent, on marque que lq cqse q ete explorer et on l add a la liste
        env->rm_tab[i]->path = 1;
        env->rm_tab[i]->parent = index;
        add_room_path(env, env->rm_tab[i]);
      }
      i++;
    }
    if (!(*env->rm_lst_path))
    {
      env->max_path--;
      return ;
    }
    if ((*env->rm_lst_path)->end)
      env->nb_path++;
  }
  return ;
}

/* Parcours la graphe en commencant par la fin, et en remontant par le parent de chaque rooms
le path est un char *, où les rooms sont renseignées par leur noms ( a changer par leur index), et delimieter par un espace

Puis on supprime les tunnels de notre path pour essayer de trouver un nouveau chemin
Chaque path commence par la room start, et fini par un "|"
*/

void get_path(t_env *env)
{
	int parent;
  int index;
  int save;

  //On prends l index de la case end et on cherche son pere
  index = env->nt_rm[1] - 1;
  parent = env->rm_tab[index]->parent;
  // On join son nom dans le path suivis d un espace pour delimiter
  env->path = ft_strrev(env->path);
  env->path = ft_joinfree(env->path, "|");
  env->path = ft_joinfree(env->path, env->rm_tab[index]->name);
  env->path = ft_joinfree(env->path, " ");
  // Tant qu on est pas sur la case start (qui na pas de pere ;( ) on continue)
	while (env->rm_tab[index]->parent != -1)
	{
    save = index;
		parent = env->rm_tab[index]->parent;
    index = env->rm_tab[parent]->index;
    env->tu_tab[save][index] = 0;
    env->tu_tab[index][save] = 0;
		env->path = ft_joinfree(env->path, env->rm_tab[index]->name);
    if (env->rm_tab[index]->parent != -1)
    {
      // On rajoute un espace dans env->path et on supprime les tunnels utilisee
      env->path = ft_joinfree(env->path, " ");
    }
	}
  env->path = ft_strrev(env->path);
}
