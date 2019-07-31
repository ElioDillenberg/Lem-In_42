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

void find_path(t_env *env, int index)
{
  t_room *room;

  if (index >= env->nt_rm[1])
    return ;
  room = env->rm_tab[index];
  ft_printf("[%s]\n", env->rm_tab[index]->name);
  find_path(env, index + 1);
}
