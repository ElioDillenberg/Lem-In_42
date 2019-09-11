/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/08/31 15:48:36 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

t_env *init_env(t_env *env)
{
	int j;

	j = 0;
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(env->rm_lst = (t_room **)ft_memalloc(sizeof(t_room *))))
	{
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->rm_lst_path = (t_room **)ft_memalloc(sizeof(t_room *))))
	{
		ft_memdel((void**)env->rm_lst);
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->path_lst = (t_path**)ft_memalloc(sizeof(t_path*) * 2)))
	{
		ft_memdel((void**)env->rm_lst_path);
		ft_memdel((void**)env->rm_lst);
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->parse = (t_parse *)ft_memalloc(sizeof(t_parse))))
	{
		ft_memdel((void**)env->path_lst);
		ft_memdel((void**)env->rm_lst_path);
		ft_memdel((void**)env->rm_lst);
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->rm_lst_path_tt = (t_room**)ft_memalloc(sizeof(t_room *))))
	{
		ft_memdel((void**)env->parse);
		ft_memdel((void**)env->path_lst);
		ft_memdel((void**)env->rm_lst_path);
		ft_memdel((void**)env->rm_lst);
		ft_memdel((void**)&env);
		return (NULL);
	}
	if (!(env->map = ft_strnew(0)))
	{
		ft_memdel((void**)env->rm_lst_path_tt);
		ft_memdel((void**)env->parse);
		ft_memdel((void**)env->path_lst);
		ft_memdel((void**)env->rm_lst_path);
		ft_memdel((void**)env->rm_lst);
		ft_memdel((void**)&env);
		return (NULL);
	}
	env->path_tab = NULL;
	env->path_lst[0] = NULL;
	env->path_lst[1] = NULL;
	env->nb_path = 0;
	env->rm_tab = NULL;
	env->tu_cut = 0;
	env->lf_path = 0;
	env->cr_path = 0;
	env->ants_end = 0;
	env->next_ant = 1;
	env->map_len = 0;
	env->round = 0;
	env->mod_ants = 0;
	env->total_rounds = 0;
	env->opt_rounds = 0;
	env->opt_paths = 0;
	env->opt_file_path = NULL;
	env->opt_turn = 0;
	env->finish = 0;
	return (env);
}

int			main(int argc, char **argv)
{
	t_env *env;
	int ret;

	(void)argv;
	env = NULL;
	if (!(env = init_env(env)))
		return (-1);
	if (argc > 1)
		if (get_option(env, argv, argc) == -1)
			return (free_all(env, 0, 0));
	if ((env->ret = parsing(env)) == -1)
		return (free_all(env, 1, -1));
	ft_putstr(env->map);
	set_max_path(env);
	if (env->max_path == 0)
		return(free_all(env, 0, 0));
	while (env->lf_path < env->max_path)
	{
		env->lf_path++;
		env->nb_path = 0;
		cut_and_reset(env, 0, 1);
		reset_path_room(env, 1);
		while (env->nb_path < env->lf_path)
		{
			if ((ret = ft_bfs(env, 0)) == -1)
			{
				print_path(env);
				return (free_all(env, 0, -1));
			}
			if (ret == 1)
				break ;
			if (get_path(env) == -1)
				return (free_all(env, 0, -1));
			if (env->tu_cut == 1)
				cut_and_reset(env, 1, 1);
			reset_path_room(env, 1);
			if (env->nb_path != env->max_path && (*env->rm_lst_path))
				ft_roomdel(env->rm_lst_path);
		}
		if (env->lf_path > 1)
		{
			if (get_opti_path(env, env->path_lst[env->cr_path]) != env->cr_path)
			{
				env->cr_path = env->cr_path == 0 ? 1 : 0;
				break ;
			}
			else
			{
				ft_path_lst_del(&(env->path_lst[env->cr_path == 0 ? 1 : 0]));
				env->path_lst[env->cr_path == 0 ? 1 : 0] = NULL;
			}
		}
		if (env->finish == 1)
			break ;
		if (env->lf_path < env->max_path )
			env->cr_path = env->cr_path == 0 ? 1 : 0;
	}
	if (!env->path_lst[env->cr_path])
		return (free_all(env, 0, 0));
	if (env->path_lst[env->cr_path]->strt_ants == 0)
		get_strt_ants(env, env->total_rounds, env->mod_ants);
	reset_buffer(env);
	result(env);
	if (env->round && env->opt_rounds)
		if (ft_printf("\n[ROUNDS : %d]\n", env->round) == -1)
			return (free_all(env, 0, -1));
	if (env->opt_paths)
		print_path(env);
	return (free_all(env, 0, 0));
}
