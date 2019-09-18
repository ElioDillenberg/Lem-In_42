/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:18:49 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/17 18:26:33 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

static void	*free_env(t_env *env)
{
	ft_memdel((void**)&env->rm_lst);
	ft_memdel((void**)&env->rm_lst_path);
	ft_memdel((void**)&env->path_lst);
	ft_memdel((void**)&env->rm_lst_path_tt);
	ft_memdel((void**)&env->parse);
	ft_memdel((void**)&env->map);
	ft_memdel((void**)&env);
	return (NULL);
}

t_env		*init_env(t_env *env)
{
	int j;

	j = 0;
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(env->rm_lst = (t_room **)ft_memalloc(sizeof(t_room *))))
		return (free_env(env));
	if (!(env->rm_lst_path = (t_room **)ft_memalloc(sizeof(t_room *))))
		return (free_env(env));
	if (!(env->path_lst = (t_path**)ft_memalloc(sizeof(t_path*) * 2)))
		return (free_env(env));
	if (!(env->parse = (t_parse *)ft_memalloc(sizeof(t_parse))))
		return (free_env(env));
	if (!(env->rm_lst_path_tt = (t_room**)ft_memalloc(sizeof(t_room *))))
		return (free_env(env));
	if (!(env->map = ft_strnew(0)))
		return (free_env(env));
	env->next_ant = 1;
	return (env);
}
