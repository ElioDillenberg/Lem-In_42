/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:16:48 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/10 15:58:48 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>

int		usage(void)
{
	ft_putstr("\nusage: ./lem_in [option]\n");
	ft_putstr("options:\n");
	ft_putstr("    no option : lem_in works normally\n");
	ft_putstr("    -rounds : displays the number of rounds\n");
	ft_putstr("    -paths : displays used paths\n");
	ft_putstr("    -duplicate : stop parsing if duplicate coordinates found\n");
	ft_putstr("    -file -[path]: reads input from file at [path]\n\n");
	return (-1);
}

int		get_option(t_env *env, char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-rounds") == 0)
			env->opt_rounds = 1;
		else if (ft_strcmp(argv[i], "-file") == 0)
		{
			if (++i >= argc)
				return (-1);
			if (!(env->opt_file_path = ft_strdup(argv[i] + 1)))
				return (-1);
		}
		else if (ft_strcmp(argv[i], "-paths") == 0)
			env->opt_paths = 1;
		else if (ft_strcmp(argv[i], "-duplicate") == 0)
			env->opt_double = 1;
		else
			return (usage());
		i++;
	}
	return (0);
}

int		print_path(t_env *env)
{
	t_path	*cr_path_print;
	t_path	*cr_room_print;

	cr_path_print = env->path_lst[env->cr_path];
	write(1, "\n", 1);
	while (cr_path_print != NULL)
	{
		if (ft_printf("PATH[%d] (len = %d) : "
				, cr_path_print->nb, cr_path_print->len) == -1)
			return (-1);
		cr_room_print = cr_path_print;
		while (cr_room_print != NULL)
		{
			if (ft_printf("[%s]",
				env->rm_tab[cr_room_print->index]->name) == -1)
				return (-1);
			if (cr_room_print->next_room != NULL)
				write(1, "--", 2);
			cr_room_print = cr_room_print->next_room;
		}
		cr_path_print = cr_path_print->next_path;
		write(1, "\n", 1);
	}
	return (0);
}
