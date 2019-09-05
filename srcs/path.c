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
/*
int   get_opti_path(t_env *env)
{
  int size_one;
  int size_two;
  int nb_path;
  int nb_path2;
  int mod_one;
  int mod_two;
  t_path *path_one;
  t_path *path_two;


  path_one = env->path_lst[0];
  path_two = env->path_lst[1];
  if (!path_one || !path_two)
    return (-1);
  size_one = 0;
  size_two = 0;
  nb_path = 0;
  nb_path2=0;
  while (path_one)
  {
    size_one += path_one->len;
    path_one = path_one->next_path;
    nb_path++;
  }
  mod_one = ((size_one + env->nt_rm[0]) % nb_path);
  size_one = ((size_one + env->nt_rm[0]) / nb_path) - 1;
  size_one += mod_one > 0 ? 1 : 0;
  while (path_two)
  {
    size_two += path_two->len;
    path_two = path_two->next_path;
    nb_path2++;
  }
  mod_two = ((size_two + env->nt_rm[0]) % nb_path2);
  size_two = ((size_two + env->nt_rm[0]) / nb_path2) - 1;
  size_two += mod_two > 0 ? 1 : 0;
  ft_printf("s1 : %d | s2 : %d\n", size_one, size_two);
  ft_printf("nbr path 1 : %d | nbr path 2 : %d\n", nb_path, nb_path2);
  if (size_one == size_two)
  {
    if (env->cr_path == 1)
    {
      env->mod_ants = mod_two;
      env->total_rounds = size_two;
      return (1);
    }
    else
    {
      env->mod_ants = mod_one;
      env->total_rounds = size_one;
      return (0);
    }
  }
  env->mod_ants = size_one < size_two ? mod_one : mod_two;
  env->total_rounds = size_one < size_two ? size_one : size_two;
  return (size_one < size_two ? 0 : 1);
}
*/
int   get_opti_path(t_env *env)
{
  t_path *path;
  int nb_path;
  int size;
  int rounds;
  int mod;

  path = env->path_lst[env->cr_path];
  size = 0;
  nb_path = 0;
  while (path)
  {
    size += path->len;
    nb_path++;
    path = path->next_path;
  }
  mod = (size + env->nt_rm[0]) % nb_path;
  rounds = ((size + env->nt_rm[0]) / nb_path) - 1;
  rounds += mod > 0 ? 1 : 0;
  if (env->total_rounds >= rounds || env->total_rounds == 0)
  {
    if (get_strt_ants(env))
    {
      env->mod_ants = mod;
      env->total_rounds = rounds;
      return (env->cr_path);
    }
  }
  return (env->cr_path == 1 ? 0 : 1);
}
