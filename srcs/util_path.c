/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 10:31:08 by thallot           #+#    #+#             */
/*   Updated: 2019/08/01 10:31:09 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void set_max_path(t_env *env)
{
  int start_connection;
  int end_connection;
	int j;

  end_connection = 0;
	start_connection = 0;
  j = 0;
	while (j < env->nt_rm[1])
	{
		if (env->tu_tab[0][j])
			start_connection++;
		j++;
	}
  j = 0;
  while (j < env->nt_rm[1])
  {
    if (env->tu_tab[env->nt_rm[1] - 1][j])
      end_connection++;
    j++;
  }
	env->max_path = start_connection > end_connection ? end_connection : start_connection;
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

void path_finder(t_env *env)
{
  int to_find;

  env->nb_path++;
  to_find = 1;
  while (to_find)
	{
		to_find = env->nb_path;
		find_path(env, 0, to_find + 1);
		if (to_find == env->nb_path)
			to_find = 0;
	}
	if (env->nb_path == 1)
		ft_putendl("NO PATH");
	else
	{
		make_valid_path(env);
		ft_printf("PATH : %s\n", env->path);
	}
}
