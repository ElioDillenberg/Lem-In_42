/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parsing_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:02:44 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/23 18:53:06 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Below function checks wether given line can be used at data for the nb of
** ants to place within ##start
*/ 

int		is_ant_nb(char *line)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (*line == 32 || (9 <= *line && *line <= 13))
		line++;
	if (line[i] == '+')
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 || ++x > 10)
			return (-1);
		if (x == 10)
			if (ft_strcmp(line, "4294967295") == -1)
				return (-1);
		i++;
	}
	return (0);
}

static int	max_min_integer(char *line)
{
	if (line[0] == '-')
	{
		if (ft_strcmp(line, "-2147483648") == -1)
			return (-1);
	}
	if (line[0] == '+')
	{
		if (ft_strcmp(line, "+2147483647") == -1)
			return (-1);
	}
	else
		if (ft_strcmp(line, "-2147483647") == -1)
			return (-1);
	return (0);
}

static int	is_coordinate(char *line)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (*line == 32 || (9 <= *line && *line <= 13))
		line++;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 || ++x > 10)
			return (-1);
		if (x == 10)
			if (max_min_integer(line) == -1)
				return (-1);
		i++;
	}
	return (0);
}

static int	check_coordinate(char *line)
{
	while (*line == ' ')
		line++;
	if (is_coordinate(line) == -1)
		return (-1);
	if (*line == '+' || *line == '-')
		line++;
	while (ft_isdigit(line) != 0)
		line++;
	while (*line == ' ')
		line++;
	if (is_coordinate(line) == -1)
		return (-1);
	if (*line == '+' || *line == '-')
		line++;
	while (ft_isdigit(line) != 0)
		line++;
	return (0);
}

/*
** Below function and the three above statics have the purpose to check wether
** given line is receivable data to build a new room
** 
*/ 

int		is_room(char *line)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	while (*line == ' ')
		line++;
	if (*line == 'L')
		return (-1);
	while (*line != ' ')
	{
		if (*line == '-')
			return (-1);
		line++;
		x = 1;
	}
	if (check_coordinates(line) == -1)
		return (-1);
	return (0);
}
