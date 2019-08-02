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
