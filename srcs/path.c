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
  int     i;
  int fin;

  i = 0;
  fin = 0;
  int free =0;
  if (index >= env->nt_rm[1] || path_nbr > env->max_path + 2 || path_nbr == env->nb_path)
    return (1);
  env->path = ft_joinfree(env->path,env->rm_tab[index]->name);
  env->path = ft_joinfree(env->path, " ");
  if (env->rm_tab[index]->start == 1)
    env->rm_tab[index]->path = path_nbr;
  //on regarde si la room end est connecte a la room actuel

  while (i < env->nt_rm[1] && free == 0)
  {
    if (env->tu_tab[i][index] == 1 && env->rm_tab[i]->path != path_nbr && env->rm_tab[i]->end == 1)
    {
      env->path = ft_joinfree(env->path, env->rm_tab[i]->name);
      env->path = ft_joinfree(env->path, "|");
      env->nb_path++;
      return (1);
    }
    i++;
  }
  i = 0;
  // On cherche une room non visitee
  while (i < env->nt_rm[1])
  {
    if (env->tu_tab[i][index] == 1 && env->rm_tab[i]->path == 0)
    {
      env->rm_tab[i]->path = path_nbr;
      free = 1;
      find_path(env, i, path_nbr);
      break ;
    }
    i++;
  }
  // Sinon on avance
  if (fin != 1 && !free && (i = get_connection(env, 0, index, path_nbr)) != -1)
    find_path(env, i, path_nbr);
  return (0);
}
