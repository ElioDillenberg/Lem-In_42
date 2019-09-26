/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parsing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:02:44 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/26 13:09:52 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>

int			exit_is_room(char **test, int ret)
{
	ft_memdel((void**)test);
	return (ret);
}

/*
** Below function checks wether given line can be used at data for the nb of
** ants to place within ##start
*/

int			is_ant_nb(char *line)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (*line == 32 || (9 <= *line && *line <= 13) || *line == '0')
		line++;
	if (line[i] == '+')
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 || ++x > 10)
			return (-1);
		i++;
	}
	return (0);
}

static int	max_min_integer(char *line)
{
	if (line[0] == '-')
	{
		if (ft_strncmp(line, "-2147483648", 11) == -1)
			return (-1);
	}
	if (line[0] == '+')
	{
		if (ft_strncmp(line, "+2147483647", 11) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "2147483647", 10) == -1)
		return (-1);
	return (0);
}

int			is_coordinate(char *line)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (*line == '\0')
		return (-1);
	while (*line == 32 || (9 <= *line && *line <= 13))
		line++;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (line[i] && ft_isdigit(line[i]) != 0)
	{
		x++;
		if (x == 10)
			if (max_min_integer(line) == -1)
				return (-1);
		i++;
	}
	return (0);
}

/*
** Below function and the three above statics have the purpose to check wether
** given line is receivable data to build a new room
*/

int			is_room(char *line, t_room **room_lst, t_env *env)
{
	size_t	i;
	char	*test;
	t_room	*cr;

	cr = *room_lst;
	i = 0;
	if (*line == 'L')
		return (-2);
	while (line[i] != ' ' && line[i])
		i++;
	if (!(test = ft_strnew(i)))
		return (-1);
	test = ft_strncpy(test, line, i);
	if (check_name(cr, test) == -1)
		return (exit_is_room(&test, -2));
	while (*line != ' ' && *line++)
		if (*line == '-')
			return (exit_is_room(&test, -1));
	if (line[0] == '\0' || i == 0 || check_room(line) == -1
			|| ft_strchr(test, '-') != NULL)
		return (exit_is_room(&test, -2));
	if (env->opt_double && (check_coordinates(line, room_lst) == -1))
		return (exit_is_room(&test, -2));
	return (exit_is_room(&test, 0));
}
