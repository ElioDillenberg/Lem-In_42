/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:42:34 by thallot           #+#    #+#             */
/*   Updated: 2019/07/30 16:42:36 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

/* Check les connections (tunnel) disponible et non utilise par un chemin*/

int  get_connection(t_env *env, int i, int index, int path_nbr)
{
  while (i < env->nt_rm[1])
  {
    if (env->tu_tab[i][index] == 1 && env->rm_tab[i]->path == 0)
    {
      env->rm_tab[i]->path = path_nbr;
      return (i);
    }
    i++;
  }
  return (-1);
}

/* Recherche un chemin depuis la case index jusqu a end
Lorqu une room est utilisée room->path passe de 0 à nbr_path
A chaque fois le chemin est join dans la chaine de caractere env->path. Lorsqu un chemin
est valide il est termine par un " | "
Le chemin est composé des nom  des rooms successif jusqu a end (certainement a remplacer par leur index, c est juste pour mieux visualier actuellement)
*/

int find_path(t_env *env, int index, int path_nbr)
{
  t_room *room;
  int     i;
  int fin;

  i = 0;
  fin = 0;
  room = NULL;
  if (index >= env->nt_rm[1] || env->nb_path == path_nbr)
    return (1);
  room = env->rm_tab[index];
  env->path = ft_joinfree(env->path, room->name);
  env->path = ft_joinfree(env->path, " ");
  if (room->start == 1)
    room->path = path_nbr;
  if (room->end == 1)
    return (1);
  while (i < env->nt_rm[1])
  {
    if (env->tu_tab[i][index] == 1 && env->rm_tab[i]->path != path_nbr && env->rm_tab[i]->end == 1)
    {
      env->path = ft_joinfree(env->path, env->rm_tab[i]->name);
      env->path = ft_joinfree(env->path, "|");
      env->nb_path++;
      env->no_path = 0;
      return (1);
    }
    i++;
  }
  if (fin != 1 && (i = get_connection(env, 0, index, path_nbr)) != -1)
    find_path(env, i, path_nbr);
  return (0);
}

void make_valid_path(t_env *env)
{
  int i;
  char *tmp;

  i = 0;
  ft_strrev(env->path);
  while (env->path[i] != '|')
    i++;
  ft_strrev(env->path);
  tmp = env->path;
  env->path = ft_strndup(env->path, ft_strlen(env->path) - i);
  ft_memdel((void **)&tmp);
}
