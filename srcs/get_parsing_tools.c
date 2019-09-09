/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/08/06 19:41:12 by edillenb         ###   ########.fr       */
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

int		build_room_tab(t_room **rm_lst, t_room ***rm_tab)
{
	t_room	*cr;
	t_room	*prev = NULL;
	t_room	*first = NULL;
	t_room	*last = NULL;
	int		len;

	cr = *rm_lst;
	len = 0;
	while (cr != NULL)
	{
		if (cr->start && cr != *rm_lst)
		{
			first = cr;
			prev->next = cr->next;
			cr = cr->next;
			first->next = *rm_lst;
			*rm_lst = first;
			len++;
		}
		else
		{
			if (cr->end && cr->next != NULL)
			{
				last = cr;
				if (cr != *rm_lst)
					prev->next = cr->next;
				else
					*rm_lst = cr->next;
				len--;
			}
			else if (cr->next == NULL && !cr->end)
			{
				cr->next = last;
				last->next = NULL;
			}
			else
				prev = cr;
			cr = cr->next;
			len++;
		}
	}
	if (!(*rm_tab = (t_room**)malloc(sizeof(t_room*) * len)))
		return (-1);
	len = 0;
	cr = *rm_lst;
	while (cr != NULL)
	{
		cr->index = len;
		(*rm_tab)[len] = cr;
		cr->visited = false;
		prev = cr;
		cr = cr->next;
		len++;
	}
	return (len);
}
