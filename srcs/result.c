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

//creer ici la fonction qui va me permettre de recuperer le nombre de fourmis par chemins
void    get_strt_ants(t_env *env)
{
    t_path  *cr;

    cr = env->path_lst[env->cr_path];
}

int     result(t_env *env)
{
    t_path  *cr;

    cr = NULL;
    ft_printf("env->total_rounds = %d\nenv->mod_ants = %d\n", env->total_rounds, env->mod_ants);
    write(1, "\n", 1);
    while (env->ants_end < env->nt_rm[0])
    {
        //looping while not all ants have arrived
        cr = env->path_lst[env->cr_path];
        if (!cr)
          env->cr_path = env->cr_path == 1 ? 0 : 1;
        else
          env->round++;
        while (cr != NULL)
        {
            //looping while we still have paths to explore
            cr = cr->tail_path;
            while (cr->prev_room != NULL)
            {
                //looping through the path starting from end until we reach first room before start
                if (cr->ant)
                {
                    if (ft_printf("L%d-%s ", cr->ant, env->rm_tab[cr->index]->name) == -1)
                        return (-1);
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
    env->round--;
    return (0);
}
