/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/18 16:17:20 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	loop_bfs(t_env *env)
{
	int ret;

	if ((ret = ft_bfs(env, 0)) == -1)
		return (-1);
	// ft_printf("sallut jsuis dans l'bfs avec ret = %d\n", ret);
	if (ret == 1)
		return (1);
	if (get_path(env) == -1)
		return (-1);
	// ft_printf("get_path? no problem\n");
	if (env->tu_cut == 1)
	{
		env->did_cut = 1;
		cut_and_reset(env, 1, 1);
	}
	reset_path_room(env, 1);
	if (env->nb_path != env->max_path && (*env->rm_lst_path))
		ft_roomdel(env->rm_lst_path, 0);
	return (0);
}

static int	check_opti_path(t_env *env)
{
	if (get_opti_path(env, env->path_lst[env->cr_path]) != env->cr_path)
	{
		env->cr_path = env->cr_path == 0 ? 1 : 0;
		return (1);
	}
	return (0);
}

static int	loop_main(t_env *env)
{
	int	ret;

	env->lf_path++;
	if (reset_or_cpy(env) == -1)
		return (-1);
	reset_path_room(env, 1);
	while (env->nb_path < env->lf_path)
	{
		if ((ret = loop_bfs(env)) == -1)
			return (-1);
		ft_printf("JSUIS SORTI DE LA LOOP DE BFS\n");
		if (ret == 1)
			break ;
	}
	if (env->lf_path > 1)
		if (check_opti_path(env) == 1)
			return (1);
	reset_dad(env);
	if (env->finish == 1)
		return (1);
	if (env->lf_path < env->max_path)
		env->cr_path = env->cr_path == 0 ? 1 : 0;
	return (0);
}

static int	after_bfs(t_env *env)
{
	if (!env->path_lst[env->cr_path])
		return (0);
	if (env->path_lst[env->cr_path]->strt_ants == 0)
		get_strt_ants(env, env->total_rounds, env->mod_ants);
	reset_buffer(env);
	result(env);
	if (env->round && env->opt_rounds)
		if (ft_printf("\n[Rounds : %d]\n", env->round) == -1)
			return (-1);
	if (env->opt_paths)
		print_path(env);
	return (0);
}

void		print_tu_tab(t_env *env)
{
	int i;
	int	j;
	int nbr_connexion;

	i = 0;
	while (i < env->nt_rm[1])
	{
		j = 0;
		nbr_connexion = 0;
		while (j < env->nt_rm[1])
		{
			if (env->tu_tab[i][j].exist && nbr_connexion++)
				ft_printf("[%s] = %s\n", env->rm_tab[i]->name, env->rm_tab[env->tu_tab[i][j].index]->name);
			j++;
		}
		env->rm_tab[i]->dad = (int *)malloc(sizeof(int) * nbr_connexion);
		env->rm_tab[i]->nb_dad = nbr_connexion;
		while (nbr_connexion--)
			env->rm_tab[i]->dad[nbr_connexion] = -1;
		ft_printf("\n");
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_env	*env;
	int		ret;

	env = NULL;
	if (!(env = init_env(env)))
		return (-1);
	if (argc > 1)
		if (get_option(env, argv, argc) == -1)
			return (free_all(env, 0, 0));
	if ((env->ret = parsing(env)) == -1)
		return (free_all(env, 1, -1));
	print_tu_tab(env);
	ft_putstr(env->map);
	set_max_path(env);
	if (env->max_path == 0)
		return (free_all(env, 0, 0));
	while (env->lf_path < env->max_path)
	{
		if ((ret = loop_main(env)) == -1)
			return (free_all(env, 0, -1));
		if (ret == 1)
			break ;
	}
	if ((ret = after_bfs(env)) == -1)
		return (free_all(env, 0, -1));
	return (free_all(env, 0, 0));
}
