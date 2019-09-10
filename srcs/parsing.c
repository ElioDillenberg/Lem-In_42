/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:38:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/10 15:50:33 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>

/*
** Here under the function that will handle the entire parsing of input
** it checks input thanks to GNL and stores the entire input into a string
** which will be used in the end to display the ant farm
** lot can be optmizied here I believe, it's easier to have a clear view at
** start tho
*/

static int	exit_parsing(char **line, int ret, t_env *env)
{
	env = check_buffer(env, &(env)->map);
	ft_memdel((void**)line);
	get_next_line(0, line, 0);
	env->parse->ret = ret;
	return (ret);
}

int			parsing_core(t_env *env, char *line)
{
	if (line[0] == '#' && line[1] != '#')
	{
		if ((if_comment(env, line)) == -1)
			return (-1);
	}
	else if ((line[0] == '#' && line[1] == '#'))
	{
		if ((if_start_end(env, line)) == -1)
			return (-1);
	}
	else if (env->parse->index == 0 && is_ant_nb(line) != -1)
	{
		if ((if_ant(env, line)) == -1)
			return (-1);
	}
	else if (env->parse->index == 1)
	{
		if ((if_room(env, line)) == -1)
			return (-1);
	}
	else if (env->parse->index == 2 && is_tunnel(line, env->rm_lst, 1) != -1)
	{
		if ((if_tunnel(env, line)) == -1)
			return (-1);
	}
	return (1);
}

int			parsing(t_env *env)
{
	char	*line;

	line = NULL;
	if (env->opt_file_path)
		env->parse->fd = open(env->opt_file_path, O_RDONLY);
	else
		env->parse->fd = 0;
	while ((env->parse->ret = get_next_line(env->parse->fd, &line, 1))
			&& env->parse->ret != -1 && env->parse->ret != 0)
	{
		if (parsing_core(env, line) == -1)
			return (exit_parsing(&line, -6, env));
		ft_memdel((void**)&line);
	}
	return (exit_parsing(&line, 0, env));
}
