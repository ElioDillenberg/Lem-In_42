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
int    get_strt_ants(t_env *env, int rounds_cr, int mod_cr)
{
    t_path  *cr;
    int     total_ants;
    int     to_send;
    // int     mod;
    // added rounds_cr instead of env->total_rouds and mod_cr instead of mod

    to_send = 0;
    total_ants = env->nt_rm[0];
    cr = env->path_lst[env->cr_path];
    // mod = env->mod_ants;
    // if (!cr)
    // {
        // env->cr_path = env->cr_path == 1 ? 0 : 1;
        // cr = env->path_lst[env->cr_path];
    // }
    while (cr != NULL)
    {
        if ((to_send = rounds_cr - cr->len + 1) <= 0)
          return (0);
        if (total_ants >= to_send)
        {
            cr->strt_ants = to_send;
            total_ants -= to_send;
        }
        else
        {
            cr->strt_ants = total_ants;
            total_ants = 0;
        }
        if (env->mod_ants > 0)
        {
            cr->strt_ants++;
            mod_cr--;
        }
        cr = cr->next_path;
    }
    cr = env->path_lst[env->cr_path];
    if (!cr)
    {
        env->cr_path = env->cr_path == 1 ? 0 : 1;
        cr = env->path_lst[env->cr_path];
    }
    return (1);
}

int     result(t_env *env)
{
    t_path  *cr;
    t_path  *head;
    char    buffer[1];
    int     no_space;

    cr = NULL;
    cr = env->path_lst[env->cr_path];
    while (env->ants_end < env->nt_rm[0])
    {
        //looping while not all ants have arrived
        cr = env->path_lst[env->cr_path];
        env->round++;
        no_space = 0;
        if (env->opt_turn)
        {
          buffer[0] = '\0';
          read(1, buffer, 1);
          if (env->opt_turn && buffer[0] == '\0')
            return (-1);
        }
        while (cr != NULL && ((env->opt_turn && buffer[0] != '\0') || env->opt_turn == 0))
        {
            //looping while we still have paths to explore
            head = cr;
            cr = cr->tail_path;
            while (cr->prev_room != NULL)
            {
                //looping through the path starting from end until we reach first room before start
                if (cr->ant)
                {
                    no_space == 0 ? no_space = 1 : write(1, " ", 1);
                    if (ft_printf("L%d-%s", cr->ant, env->rm_tab[cr->index]->name) == -1)
                        return (-1);
                    if (cr->next_room == NULL)
                        env->ants_end++;
                    else
                        cr->next_room->ant = cr->ant;
                    cr->ant = 0;
                }
                if ((cr->prev_room->len && env->ants_end < env->nt_rm[0] && env->next_ant <= env->nt_rm[0] && head->strt_ants > 0) || head->len == 1 || (env->lf_path == 1 && cr->prev_room->len && env->ants_end < env->nt_rm[0] &&env->next_ant <= env->nt_rm[0]) )
                {
                    cr->ant = env->next_ant++;
                    head->strt_ants--;
                }
                cr = cr->prev_room;
            }
            cr = cr->next_path;
        }
        write(1, "\n", 1);
    }
    env->round--;
    return (0);
}
