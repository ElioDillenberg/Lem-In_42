/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bfs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:26:28 by thallot           #+#    #+#             */
/*   Updated: 2019/08/01 16:26:30 by thallot          ###   ########.fr       */
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
	env->max_path = start > end ? end : start;
}

void check_path(t_env *env)
{
  int i;
  char **tab;

  i = -1;
  tab = NULL;
  if (env->nb_path)
  {
    tab = ft_strsplit(env->path, '|');
    while (tab[++i])
    {
      // Si le parcours n a pas trouve de chemin valide on le supprimne
      if (tab[i][0] == ' ')
        delete_path(env);
      else
        ft_printf("PATH [%d] : %s\n", i,  tab[i]);
    }
  }
  i = 0;
  free_tab(tab);
}

void delete_path(t_env *env)
{
  int i;
  char *tmp;

  i = 0;
  while (env->path[i] != '|')
    i++;
  i++;
  tmp = env->path;
  env->path = ft_strrev(env->path);
  env->path = ft_strndup(tmp, i);
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
