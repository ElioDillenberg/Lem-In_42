/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:38:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/22 19:31:37 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	get_command(char *line, int *command)
{
	if (ft_strcmp(line, "##start") == 0)
		*commmand = 1;
	else if (ft_strcmp(line, "##end") == 0)
		*command = 2;
}

int		get_ant_nb(char *line, size_t **ant_tab, size_t *nb_ants)
{
	size_t	i;

	i = 0;
	*nb_ants = ft_atoui(line);
	if (!(*ant_tab = (size_t*)malloc(sizeof(size_t) * *nb_ants)))
		return (-1);
	while (i < *nb_ants) 
	{
		(*ant_tab)[i] = i + 1;
		i++;
	}
}

int		is_ant_nb(char *line, size_t **ant_tab)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (*line == 32 || (9 <= *line && *line <= 13))
		line++;
	if (*line == '-' || *line == '+')
		line++;
	while (*line)
	{
		if (ft_isdigit(*line) == 0 || ++x > 10)
			return (-1);
		if (x == 10)
			if (ft_strcmp(line, "4294967295") == -1)
				return (-1);
		line++;
	}
	return (0);
}

/*
**
**
**
*/

int		exit_parsing(char **line, int ret)
{
	ft_memdel((void**)line);
	get_next_line(0, line, 0);
	return (ret);
}

int		parsing(t_room **room_lst, size_t **ant_tab, size_t *nb_ants)
{
	char	*to_print;
	char	*line;
	int		index;
	int		command;

	command = 0;
	index = 0;
	while ((ret = get_next_line(0, &line, 1)) && ret != -1 && ret != 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			if (!(ft_strjoinfr(to_print, line)))
				return (-1);
		}
		else if (line[0] == '#' && line[1] == '#')
			get_command(line, &command);
		else if (index == 0 && is_ant_nb(line))
		{
			if (!(get_ant_nb(line, ant_tab, nb_ants)))
				return (exit_parsing(&line, -1))
		}
		else if (index == 1)
		{
			if (is_room(line) != -1)
				get_room(line, room_lst, command);
			else if (is_tunnel(line) != -1)
				get_tunnel(line, room_lst, &index);
		}
		else if (index == 2 && is_tunnel(line))
			get_tunnel(line, room_lst, &index);
		else
			return (exit_parsing(&line, 0));
		}
		ft_memdel((void**)&line);
	}
	get_next_line(0, &line, 0);
}
