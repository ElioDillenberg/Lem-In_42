/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:30:01 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/02 19:30:03 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

void       result(t_env *env)
{
    t_path  *cr;

<<<<<<< HEAD
    cr = NULL;
    ft_printf("\n");
    while (env->ants_end < env->nt_rm[0])
    {
        //looping while not all ants have arrived
        cr = env->path_lst[env->cr_path];
        while (cr != NULL)
        {
            //looping while we still have paths
            cr = cr->tail_path->prev_room;
            while (cr->prev_room != NULL)
            {
                //looping while there are rooms to explore within this path
                if (cr->ant)
                {
                    cr->next_room->ant = cr->ant;
                    cr->ant = 0;
                    ft_printf("L%d-%s ", cr->next_room->ant, env->rm_tab[cr->next_room->index]->name);
                    if (cr->next_room->next_room == NULL)
                        env->ants_end++;
                }
                if (cr->prev_room->len && env->ants_end < env->nt_rm[0] && env->next_ant <= env->nt_rm[0])
                {
                    cr->ant = env->next_ant++;
                    ft_printf("L%d-%s ", cr->ant, env->rm_tab[cr->index]->name);
                }
                cr = cr->prev_room;
            }
            cr = cr->next_path;
        }
        ft_printf("\n");
    }    
=======
    cr = env->path_lst[env->cr_path];
    if (env->cr_path == 0)
        return;
>>>>>>> 15344258423ad593248ecff76a0980b7b79d3f61
}