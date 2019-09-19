/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:10:50 by thallot           #+#    #+#             */
/*   Updated: 2019/09/18 15:33:14 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int		check_coordinates_lst(int x, int y, t_room **room_lst)
{
	t_room *cr;

	cr = *room_lst;
	while (cr != NULL)
	{
		if (cr->x == x)
			if (cr->y == y)
				return (-1);
		cr = cr->next;
	}
	return (0);
}

int		check_coordinates(char *line, t_room **room_lst)
{
	int	x;
	int y;

	while (*line == ' ')
		line++;
	if (is_coordinate(line) == -1)
		return (-1);
	x = ft_atoi(line);
	if (*line == '+' || *line == '-')
		line++;
	while (ft_isdigit(*line) != 0)
		line++;
	while (*line == ' ')
		line++;
	if (is_coordinate(line) == -1)
		return (-1);
	if (*line == '+' || *line == '-')
		line++;
	y = ft_atoi(line);
	if (check_coordinates_lst(x, y, room_lst) == -1)
		return (-1);
	return (0);
}

int		check_name(t_room *cr, char *test)
{
	while (cr != NULL)
	{
		if (ft_strcmp(test, cr->name) == 0)
		{
			free(test);
			return (-1);
		}
		cr = cr->next;
	}
	return (1);
}

int		check_room(char *line)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i == 0)
		return (-1);
	if (line[i] == ' ')
		i++;
	else
		return (-1);
	while (ft_isdigit(line[i + j]))
		j++;
	if (line[i + j] != '\0' || j == 0)
		return (-1);
	return (1);
}
