/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/25 18:04:45 by edillenb         ###   ########.fr       */
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

int		get_hash(char *name, int len_hash_tab)
{
	int		hash;

	hash = 0;
	while (*name)
	{
		hash += *name;
		name++;
	}
	hash /= len_hash_tab;
	return (hash);
}

int		build_hash_tab(t_room *room_lst, t_room **hash_tab)
{
	t_room	*cr;
	size_t	len;
	int		hash;

	cr = room_lst;
	len = 0;
	while (cr != NULL)
	{
		cr = cr->next;
		len++;
	}
	if (!(*hash_tab = (t_room*)malloc(sizeof(t_room) * len)))
		return (-1);
	cr = room_lst;
	while (cr != NULL)
	{
		// need to create a function that will place the hash at the right place here
		hash = get_hash(cr->name, len);
		//if (*(hash_tab)[hash] == NULL)
	//		(*hash_tab)[hash] = cr;
		// does this work? doubts here, maybe changing cr will affect *hash_tab[hash]
		cr = cr->next;
	}
	return (0);
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
