/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tunnel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:59:34 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/29 18:40:26 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>

int		init_tu_tab(int ***tu_tab, int *nt_rm)
{
	int	i;
	int	j;

	i = 0;
	if (!(*tu_tab = (int**)malloc(sizeof(int*) * nt_rm[1])))
		return (-1);
	while (i < nt_rm[1])
		if (!((*tu_tab)[i++] = (int*)malloc(sizeof(int) * nt_rm[1])))
			return(-1);
	i = 0;
	while (i < nt_rm[1])
	{
		j = 0;
		while (j < nt_rm[1])
		{
			(*tu_tab)[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

int		is_tunnel(char *line, t_room **room_lst)
{
	size_t	i;
	size_t	cmp;
	t_room *cr;

	i = 0;
	cmp = 0;
	cr = *room_lst;
	while (line[i] != '-' && line[i] != '\0')
		i++;
	if (line[i] == '-')
		line[i] = '\0';
	else
		return (-1);
	while (cr != NULL)
	{
		if (strcmp(line, cr->name) == 0)
		{
			cmp++;
			break;
		}
		cr = cr->next;
	}
	line[i] = '-';
	while (*line != '-' && *line)
		line++;
	if (*line == '-')
		line++;
	else
		return (-1);
	cr = *room_lst;
	while (cr != NULL)
	{
		if (strcmp(line, cr->name) == 0)
		{
			cmp++;
			break;
		}
		cr = cr->next;
	}
	if (cmp != 2)
	{
		ft_printf("cmp != 2\n");
		return (-1);
	}
	return (0);
}

void	get_tunnel(char *line, int *nt_rm, int **tu_tab, t_room **room_tab)
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
	while (one < nt_rm[1])
	{
		if (strcmp(line, (room_tab[one])->name) == 0)
			break;
		one++;
	}
	line[i] = '-';
	while (*line != '-' && *line)
		line++;
	line++;
	while (two < nt_rm[1])
	{
		if (strcmp(line, room_tab[two]->name) == 0)
			break;
		two++;
	}
	tu_tab[one][two] = 1;
	tu_tab[two][one] = 1;
}
