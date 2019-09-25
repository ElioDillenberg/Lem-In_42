/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:44:19 by thallot           #+#    #+#             */
/*   Updated: 2019/09/25 14:55:40 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

int		if_comment(t_env *env, char *line, int opt)
{
	if (opt && !(strcat_big(line, &(env)->map, env)))
		return (-1);
	return (1);
}

int		if_start_end(t_env *env, char *line)
{
	if (get_command(line, env->parse->start_end) == -1)
		return (-2);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	return (1);
}

int		if_ant(t_env *env, char *line)
{
	if (is_ant_nb(line) == -1)
		return (-2);
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-2);
	env->nt_rm[0] = ft_atoui(line);
	if (env->nt_rm[0] > 100000 || env->nt_rm[0] <= 0)
		return (-2);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	env->parse->index++;
	return (1);
}

int		if_room(t_env *env, char *line)
{
	int ret;

	if ((ret = is_room(line, env->rm_lst, env)) == -2 && env->parse->index == 1)
		return (-2);
	else if (ret >= 0)
	{
		if ((add_room(line, env->rm_lst, env->parse->start_end) == -1)
				|| (!(strcat_big(line, &(env)->map, env))))
			return (-1);
	}
	else if (is_tunnel(line, env->rm_lst, 0, 0) == 0)
	{
		if (env->parse->start_end[0] != 2 || env->parse->start_end[1] != 2)
			return (-2);
		if (build_room_tab(env) == -1
			|| init_tu_tab(&(env)->tu_tab, env->nt_rm) == -1)
			return (-1);
		if (get_tunnel(env, line) == -1)
			return (-2);
		if (env->parse->index++ && !(strcat_big(line, &(env)->map, env)))
			return (-1);
	}
	else
		return (-2);
	return (1);
}

int		if_tunnel(t_env *env, char *line)
{
	if (is_tunnel(line, env->rm_lst, 1, 0) == -2)
		return (-2);
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-2);
	if (get_tunnel(env, line) == -1)
		return (-2);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	return (1);
}
