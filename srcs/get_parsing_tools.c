/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/08/05 19:32:27 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

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
		ft_printf("LOOPLOL\n");
		ft_printf("adr_cr = %p\n", cr);
		ft_printf("adr_first = %p\n", first);
		ft_printf("adr_last = %p\n", last);
		ft_printf("adr_prev = %p\n", prev);
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
				prev->next = cr->next;
				len--;
			}
			else if (cr->next == NULL && !cr->end)
			{
				cr->next = last;
				last->next = NULL;
				last = NULL;
			}
			prev = cr;
			cr = cr->next;
			len++;
		}
	}
	first = NULL;
	ft_printf("\nlen = %d\n\n", len);
	if (!(*rm_tab = (t_room**)malloc(sizeof(t_room*) * len)))
		return (-1);
	len = 0;
	cr = *rm_lst;
	while (cr != NULL)
	{
		ft_printf("adr_cr = %p\n", cr);
		ft_printf("adr_cr->next = %p\n", cr->next);
		ft_printf("cr->name = %s\n\n", cr->name);
//		ft_printf("len = %d\n", len);
		cr->index = len;
		(*rm_tab)[len] = cr;
		prev = cr;
//		ft_printf("cr->name = %s\n", cr->name);
		cr = cr->next;
		len++;
	}
	ft_printf("\nlen = %d\n\n", len);
	return (len);
}
