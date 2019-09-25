/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/25 15:45:41 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

int		get_command(char *line, int *start_end)
{
	if (ft_strcmp(line, "##start") == 0)
	{
		if (start_end[0] == 0 && start_end[1] != 1)
			start_end[0] = 1;
		else
			return (-1);
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		if (start_end[1] == 0 && start_end[0] != 1)
			start_end[1] = 1;
		else
			return (-1);
	}
	return (0);
}

int		get_room(char *line, t_room *room)
{
	size_t i;

	i = 0;
	while (*line && *line == ' ')
		line++;
	while (line[i] && line[i] != ' ')
		i++;
	if (!(room->name = ft_strsub((const char **)&line, 0, i, 0)))
		return (-1);
	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	room->x = ft_atoi(line);
	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	room->y = ft_atoi(line);
	return (0);
}

int		get_room_tab(t_env *env, int len)
{
	t_room *cr;

	if (!(env->rm_tab = (t_room**)malloc(sizeof(t_room*) * len)))
		return (-1);
	len = 0;
	cr = *env->rm_lst;
	while (cr != NULL)
	{
		env->rm_tab[len] = cr;
		cr = cr->next;
		len++;
	}
	return (0);
}

int		add_tunnel(t_env *env, int index, int to_add)
{
	int i;

	i = 0;
	if (index == to_add)
		return (-1);
	while (env->tu_tab[index][i].exist != false)
	{
		if (env->tu_tab[index][i].index == to_add)
			return (-1);
		i++;
	}
	env->tu_tab[index][i].exist = true;
	env->tu_tab[index][i].index = to_add;
	env->tu_tab[index][i].status = 1;
	return (1);
}

int		get_tunnel(t_env *env, char *line)
{
	size_t	i;
	int		one;
	int		two;

	i = 0;
	one = 0;
	two = 0;
	while (line[i] != '-' && line[i] != '\0')
		i++;
	line[i] = '\0';
	while (one < env->nt_rm[1] && ft_strcmp(line, (env->rm_tab[one])->name))
		one++;
	line[i] = '-';
	while (*line != '-' && *line != '\0')
		line++;
	line++;
	while (two < env->nt_rm[1] && ft_strcmp(line, env->rm_tab[two]->name))
		two++;
	if (add_tunnel(env, one, two) == -1)
		return (-1);
	if (add_tunnel(env, two, one) == -1)
		return (-1);
	return (1);
}
