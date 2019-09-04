/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:30:01 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/03 16:46:40 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>

void       result(t_env *env)
{
    t_path  *cr;

    cr = NULL;
    write(1, "\n", 1);
    while (env->ants_end < env->nt_rm[0])
    {
        //looping while not all ants have arrived
        cr = env->path_lst[env->cr_path];
        if (!cr)
          env->cr_path = env->cr_path == 1 ? 0 : 1;
        while (cr != NULL)
        {
            //looping while we still have paths to explore
            cr = cr->tail_path;
            while (cr->prev_room != NULL)
            {
                //looping through the path starting from end until we reach first room before start
                if (cr->ant)
                {
                    ft_printf("L%d-%s ", cr->ant, env->rm_tab[cr->index]->name);
                    if (cr->next_room == NULL)
                        env->ants_end++;
                    else
                        cr->next_room->ant = cr->ant;
                    cr->ant = 0;
                }
                if (cr->prev_room->len && env->ants_end < env->nt_rm[0] && env->next_ant <= env->nt_rm[0])
                    cr->ant = env->next_ant++;
                cr = cr->prev_room;
            }
            cr = cr->next_path;
        }
        write(1, "\n", 1);
    }
    cr = env->path_lst[env->cr_path];
    if (env->cr_path == 0)
        return;
}
