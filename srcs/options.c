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