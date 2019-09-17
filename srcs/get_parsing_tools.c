/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/11 15:15:30 by thallot          ###   ########.fr       */
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
		if (start_end[0] == 0)
			start_end[0] = 1;
		else
			return (-1);
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		if (start_end[1] == 0)
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
	while (*line == ' ')
		line++;
	while (line[i] != ' ')
		i++;
	if (!(room->name = ft_strsub((const char **)&line, 0, i, 0)))
		return (-1);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	room->x = ft_atoi(line);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	room->y = ft_atoi(line);
	return (0);
}

t_room	**get_room_tab(t_room ***rm_tab, t_room **rm_lst, int len)
{
	t_room *cr;
	t_room *prev;

	if (!(*rm_tab = (t_room**)malloc(sizeof(t_room*) * len)))
		return (NULL);
	len = 0;
	cr = *rm_lst;
	while (cr != NULL)
	{
		cr->index = len;
		(*rm_tab)[len] = cr;
		prev = cr;
		cr = cr->next;
		len++;
	}
	return (*rm_tab);
}

void add_tunnel(t_env *env, int index, int to_add)
{
	int i;

	i = 0;
	while (env->tu_tab[index][i].exist != false)
		i++;
	env->tu_tab[index][i].exist = true;
	env->tu_tab[index][i + 1].exist = true;
	env->tu_tab[index][i].index = to_add;
	env->tu_tab[index][i].status = 1;
}

void	get_tunnel(t_env *env, char *line)
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
	while (one < env->nt_rm[1] && strcmp(line, (env->rm_tab[one])->name) != 0)
		one++;
	line[i] = '-';
	while (*line != '-' && *line != '\0')
		line++;
	line++;
	while (two < env->nt_rm[1] && strcmp(line, env->rm_tab[two]->name) != 0)
		two++;
	add_tunnel(env, one, two);
	add_tunnel(env, two, one);
}
