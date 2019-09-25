/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/24 19:41:57 by edillenb         ###   ########.fr       */
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
	if (ret == 1)
		return (1);
	if (get_path(env) == -1)
		return (-1);
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
		if (ret == 1)
			break ;
	}
	if (env->lf_path > 1)
		if (check_opti_path(env) == 1)
			return (1);
	if (env->finish == 1 || env->path_lst[env->cr_path]->len == 1)
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

int			main(int argc, char **argv)
{
	t_env	*env;
	int		ret;

	env = NULL;
	if (!(env = init_env(env)))
		return (-1);
	if (argc > 1)
		if (get_option(env, argv, argc) == -1)
			return (free_all(env, 0));
	if ((env->ret = parsing(env)) == -1 || set_daddy(env) == -1)
		return (free_all(env, 1));
	ft_putstr(env->map);
	set_max_path(env);
	if (env->max_path == 0)
		return (free_all(env, 0));
	while (env->lf_path < env->max_path)
	{
		if ((ret = loop_main(env)) == -1)
			return (free_all(env, 0));
		if (ret == 1)
			break ;
	}
	if ((ret = after_bfs(env)) == -1)
		return (free_all(env, 0));
	return (free_all(env, 0));
}
