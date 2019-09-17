/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:55:16 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/17 15:32:25 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	*free_env(t_env **env)
{
	ft_memdel((void**)(*env)->rm_lst);
	ft_memdel((void**)(*env)->rm_lst_path);
	ft_memdel((void**)(*env)->path_lst);
	ft_memdel((void**)(*env)->rm_lst_path_tt);
	ft_memdel((void**)(*env)->parse);
	ft_memdel((void**)(*env)->map);
	ft_memdel((void**)&(*env));
	return (NULL);
}

t_env		*init_env(t_env *env)
{
	int j;

	j = 0;
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(env->rm_lst = (t_room **)ft_memalloc(sizeof(t_room *))))
		return (free_env(&env));
	if (!(env->rm_lst_path = (t_room **)ft_memalloc(sizeof(t_room *))))
		return (free_env(&env));
	if (!(env->path_lst = (t_path**)ft_memalloc(sizeof(t_path*) * 2)))
		return (free_env(&env));
	if (!(env->parse = (t_parse *)ft_memalloc(sizeof(t_parse))))
		return (free_env(&env));
	if (!(env->rm_lst_path_tt = (t_room**)ft_memalloc(sizeof(t_room *))))
		return (free_env(&env));
	if (!(env->map = ft_strnew(0)))
		return (free_env(&env));
	env->next_ant = 1;
	return (env);
}

static int	loop_bfs(t_env *env)
{
	int ret;

	if ((ret = ft_bfs(env, 0)) == -1)
	{
		print_path(env);
		return (-1);
	}
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

t_path		*copy_room(t_path *pnocr)
{
	t_path	*new;

	if (!(new = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	new->nb = pnocr->nb;
	new->len = pnocr->len;
	new->index = pnocr->index;
	new->ant = pnocr->strt_ants;
	return (new);
}

t_path		*copy_path_lst(t_env *env)
{
	int		not_cr;
	t_path	*new_head;
	t_path	*new_cr;
	t_path	*pnocr;

	new_head = NULL;
	new_cr = NULL;
	not_cr = env->cr_path == 0 ? 1 : 0;
	pnocr = env->path_lst[not_cr];
	while (pnocr->next_path)
		pnocr = pnocr->next_path;
	pnocr = pnocr->tail_path;
	while (pnocr)
	{
		if (new_head == NULL)
		{
			if (!(new_head = copy_room(pnocr)))
				return (NULL);
			new_head->tail_path = new_head;
		}
		else
		{
			if (!(new_cr = copy_room(pnocr)))
				return (NULL);
			new_head->prev_room = new_cr;
			new_cr->next_room = new_head;
			new_cr->tail_path = new_head->tail_path;
			new_head = new_cr;
		}
		pnocr = pnocr->prev_room;
	}
	return (new_head);
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

int			get_last_path_lst(t_env *env)
{
	t_path	*cr;

	cr = env->path_lst[env->cr_path];
	if (!cr)
	{
		if (!(env->path_lst[env->cr_path] = copy_path_lst(env)))
			return (-1);
	}
	else
	{
		while (cr->next_path)
			cr = cr->next_path;
		if (!(cr->next_path = copy_path_lst(env)))
			return (-1);
	}
	return (0);
}

static int	loop_main(t_env *env)
{
	int	ret;

	env->lf_path++;
	if (env->did_cut == 1)
	{
		ft_path_lst_del(&(env->path_lst[env->cr_path]));
		env->path_lst[env->cr_path] = NULL;
		env->did_cut = 0;
		cut_and_reset(env, 1, 1);
	}
	else if (env->lf_path > 1)
	{
		if (get_last_path_lst(env) == -1)
			return (-1);
	}
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
		if (ft_printf("\n[ROUNDS : %d]\n", env->round) == -1)
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
			return (free_all(env, 0, 0));
	if ((env->ret = parsing(env)) == -1)
		return (free_all(env, 1, -1));
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
