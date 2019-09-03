/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bfs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:28 by thallot           #+#    #+#             */
/*   Updated: 2019/08/12 17:12:02 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

/*
Pour connaitre le maximum de path possible on regarde le nombre de tunnel sur start et end
Puis on choisis le plus petit de deux
*/

void set_max_path(t_env *env)
{
  int start;
  int end;
	int j;

  end = 0;
	start = 0;
  j = 0;
	while (j < env->nt_rm[1])
	{
		if (env->tu_tab[0][j])
			start++;
		j++;
	}
  j = 0;
  while (j < env->nt_rm[1])
  {
    if (env->tu_tab[env->nt_rm[1] - 1][j])
      end++;
    j++;
  }
  //chosing between connections between start and end
	env->max_path = start > end ? end : start;
  //chosing between max_path and number of ants
  env->max_path = env->nt_rm[0] < env->max_path ? env->nt_rm[0] : env->max_path;
  // ft_printf("start = %d\n", start);
  // ft_printf("end = %d\n", end);
  // ft_printf("env->nt_rm = %d\n", env->nt_rm[0]);
}

/*
Check si tous les chemins sont valide. Apres le 1er parcours de BFS lorsque des chemins sont bouche il est possible
qu aucun chemin ne mene a la sortie, dans ce cas on le supprime.
*/

int		check_path(t_env *env)
{
  int	i;
  int	j;
  char	**tab;

  i = -1;
  j = 0;
  tab = NULL;
  if (!(env->path_tab = (int **)malloc(sizeof(int *) * env->nb_path)))
    return (-1);
  if (env->nb_path)
  {
    if (!(tab = ft_strsplit(env->path, '|')))
	  {
		  ft_memdel((void**)env->path_tab);
		  return (-1);
	  }
  while (tab[++i])
  {
    //Si le chemin n est valide on ne le traite pas (il commence par un espace au lieu de commencer par lindex de start)
    if (tab[i][0] != ' ')
      if (create_path_tab(env, tab[i], (env->nb_path - 1) - j++) == -1)
      {
        free_tab(tab);
        return (-1);
      }
		// (env->nb_path - 1) -j pour que le premier chemin trouvé (le plus court) soit a l index 0
  }
  }
  free_tab(tab);
  return (0);
}

/*
Cree un tableau int** qui reference tous les path
Chaque path est compose des index des rooms utilisee
la fin d un path est egale a -1 ce qui permet de parcourir le tableau sans connaitre sa longueur
Le tout est stocke dans env->path_tab
*/

int		create_path_tab(t_env *env, char *str, int index)
{
  char **tab;
  int i;
  int nb_room;

  i = -1;
  nb_room = 1;
  while (str[++i])
    nb_room += str[i] == ' ' ? 1 : 0;
  if (!(env->path_tab[index] = (int *)malloc(sizeof(int) * (nb_room + 1))))
    return (-1);
  i = -1;
  if (!(tab = ft_strsplit(str, ' ')))
	  return (-1);
  while (tab[++i])
    env->path_tab[index][i] = ft_atoui(tab[i]);
  env->path_tab[index][i] = -1;
  free_tab(tab);
  return (0);
}

void delete_path(t_env *env)
{
  int i;
  char *tmp;

  i = 0;
  while (env->path[i] != '|' && env->path[i])
    i++;
  i++;
  tmp = env->path;
  env->path = ft_strrev(env->path);
  env->path = ft_strndup(tmp, i);
  env->nb_path--;
  ft_memdel((void **)&tmp);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_memdel((void **)&tab[i]);
		i++;
	}
	ft_memdel((void **)&tab);
}
