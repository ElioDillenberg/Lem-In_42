/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:44:19 by thallot           #+#    #+#             */
/*   Updated: 2019/09/10 15:48:35 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

int		if_comment(t_env *env, char *line, int opt)
{
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-1);
	if (opt && !(strcat_big(line, &(env)->map, env)))
		return (-1);
	return (1);
}

int		if_start_end(t_env *env, char *line)
{
	if (get_command(line, env->parse->start_end) == -1)
		return (-1);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	return (1);
}

int		if_ant(t_env *env, char *line)
{
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-1);
	env->nt_rm[0] = ft_atoui(line);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	env->parse->index++;
	return (1);
}

int		if_room(t_env *env, char *line)
{
	if (is_room(line, env->rm_lst, env) == -2 && env->parse->index == 1)
		return (-1);
	if (is_room(line, env->rm_lst, env) != -1)
	{
		if (add_room(line, env->rm_lst, env->parse->start_end) == -1)
			return (-1);
		if (!(strcat_big(line, &(env)->map, env)))
			return (-1);
	}
	else if (is_tunnel(line, env->rm_lst, 0) != -1)
	{
		if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
			return (-1);
		if ((env->nt_rm[1] = build_room_tab(env->rm_lst, &(env)->rm_tab)) == -1)
			return (-1);
		if (init_tu_tab(&(env)->tu_tab, env->nt_rm) == -1)
			return (-1);
		get_tunnel(env, line);
		env->parse->index++;
		if (!(strcat_big(line, &(env)->map, env)))
			return (-1);
	}
	else
		return (-1);
	return (1);
}

int		if_tunnel(t_env *env, char *line)
{
	if (is_tunnel(line, env->rm_lst, 1) == -2)
		return (-1);
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-1);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	get_tunnel(env, line);
	return (1);
}
