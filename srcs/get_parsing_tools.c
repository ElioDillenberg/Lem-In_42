/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/27 20:07:34 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	get_command(char *line, int *command)
{
	if (ft_strcmp(line, "##start") == 0)
		*command = 1;
	else if (ft_strcmp(line, "##end") == 0)
		*command = 2;
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
	ft_printf("This is room_name : %s\n", room->name);
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

int		build_room_tab(t_room **rm_lst, t_room **rm_tab)
{
	t_room	*cr;
	t_room	*prev = NULL;
	t_room	*last = NULL;
	int		len;
	int		i;

	cr = *rm_lst;
	len = 0;
	i = 0;
	while (cr != NULL)
	{
		if (cr->start && cr != *rm_lst)
		{
			prev->next = cr->next;
			cr->next = *rm_lst;
			*rm_lst = cr;
		}
		else if (cr->end && cr->next != NULL)
		{
			prev->next = cr->next;
			last = cr;
		}
		else if (cr->next == NULL && cr->end == false)
		{
			cr->next = last;
			last->next = NULL;
		}
		prev = cr;
		cr = cr->next;
		len++;
	}
	if (!(*rm_tab = (t_room*)malloc(sizeof(t_room) * len)))
		return (-1);
	cr =  *rm_lst;
	while (cr != NULL)
	{
		(*rm_tab)[i] = *cr;
		cr = cr->next;
		i++;
	}
	return (len);
}

/*
int		get_tunnels(char *line, t_room *room, t_room **hash_tab)
{
	t_room *cr;
	size_t	len;

	cr = room;
	len = 0;
	while (cr != NULL)
	{
		cr = cr->next;
		len++;
	}
	if (!(*hash_tab = (t_room*)malloc(sizeof(t_room) * len)))
		return (-1);
	return (0);
}
*/
