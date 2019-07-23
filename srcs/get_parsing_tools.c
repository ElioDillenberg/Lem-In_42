/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:03:19 by edillenb          #+#    #+#             */
/*   Updated: 2019/07/23 19:29:00 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	get_command(char *line, int *command)
{
	if (ft_strcmp(line, "#include start") == 0)
		*commmand = 1;
	else if (ft_strcmp(line, "#include end") == 0)
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
	if (!(t_room->name = ft_strsub((const char **)line, 0, i)))
		return (-1);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	t_room->x = ft_atoi(line);
	while (*line != ' ')
		line++;
	while (*line == ' ')
		line++;
	t_room->y = ft_atoi(line);
}
