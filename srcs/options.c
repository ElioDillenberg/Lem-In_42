/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:16:48 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/05 14:16:51 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

int     get_option(t_env *env, char **argv)
{
    if (ft_strcmp(argv[1], "-rounds") == 0)
        env->opt_rounds = 1;
    else if (ft_strcmp(argv[1], "-file") == 0)
    {
        if (!(env->opt_file_path = ft_strdup(argv[2] + 1)))
            return (-1);
    }
    else if (ft_strcmp(argv[1], "-paths") == 0)
        env->opt_paths = 1;
    else if (ft_strcmp(argv[1], "-turn") == 0)
        env->opt_turn = 1;
    else
    {
        ft_putstr("\nusage: ./lem_in [option]\n");
        ft_putstr("options:\n");
        ft_putstr("    no option : lem_in works normally\n");
        ft_putstr("    -rounds : displays the number of rounds\n");
        ft_putstr("    -paths : displays used paths\n");
        ft_putstr("    -file -[path]: reads input from file at [path]\n");
        return (-1);
    }
    return (0);
}

void print_path(t_env *env)
{
  t_path  *cr_path_print;
  t_path *cr_room_print;

  cr_path_print = env->path_lst[env->cr_path];
   while (cr_path_print != NULL)
   {
   	ft_printf("PATH [%d] (len = %d) : ", cr_path_print->nb, cr_path_print->len);
   	cr_room_print = cr_path_print;
   	while (cr_room_print != NULL)
  	{
  		 ft_printf("[Index : %d | Salle : %s] - ", cr_room_print->index, env->rm_tab[cr_room_print->index]->name);
   		cr_room_print = cr_room_print->next_room;
   	}
   	cr_path_print = cr_path_print->next_path;
   	 ft_printf("\n");
   }
 ft_printf("\n");
}
