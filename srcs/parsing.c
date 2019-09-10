/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:38:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/08/12 11:38:56 by edillenb         ###   ########.fr       */
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

static int exit_parsing(char **line, int ret, t_env *env)
{
	//ft_printf("CODERROR : %d\n", ret);
	env = check_buffer(env, &(env)->map);
	ft_memdel((void**)line);
	get_next_line(0, line, 0);
	env->parse->ret = ret;
	return (ret);
}

int if_comment(t_env *env, char *line)
{
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-1);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	return (1);
}

int		if_start_end(t_env *env, char *line)
{
	if (get_command(line, env->parse->start_end) == -1)
		return (-1);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	return (1);
}

int		if_ant(t_env *env, char *line)
{
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-1);
	env->nt_rm[0] = ft_atoui(line);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	env->parse->index++;
	return (1);
}

int	if_room(t_env *env, char *line)
{
	if (is_room(line, env->rm_lst) == -2 && env->parse->index == 1)
		return (-1);
	if (is_room(line, env->rm_lst) != -1)
	{
		if (add_room(line, env->rm_lst, env->parse->start_end) == -1)
			return (-1);
		if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	}
	else if (is_tunnel(line, env->rm_lst, 0) != -1)
	{
		if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
			return (-1);
		if ((env->nt_rm[1] = build_room_tab(env->rm_lst, &(env)->rm_tab)) == -1)
			return (-1);
		if (init_tu_tab(&(env)->tu_tab, env->nt_rm) == -1)
			return (-1);
		get_tunnel(env, line);
		env->parse->index++;
		if (!(strcat_big(line, &(env)->map, env)))
			return (-1);
	}
	else
		return (-1);
	return (1);
}

int		if_tunnel(t_env *env, char *line)
{
	if (is_tunnel(line, env->rm_lst, 1) == -2)
		return (-1);
	if (env->parse->start_end[0] == 1 || env->parse->start_end[1] == 1)
		return (-1);
	if (!(strcat_big(line, &(env)->map, env)))
		return (-1);
	get_tunnel(env, line);
	return (1);
}
/*
**
**
*/

int parsing(t_env *env)
{
	char	*line;

	line = NULL;
	env->parse->fd = env->opt_file_path ? open(env->opt_file_path, O_RDONLY) : 0;
	while ((env->parse->ret = get_next_line(env->parse->fd, &line, 1)) && env->parse->ret != -1 && env->parse->ret != 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			if ((if_comment(env, line)) == -1)
				return (exit_parsing(&line, -1, env));
		}
		else if ((line[0] == '#' && line[1] == '#'))
		{
			if ((if_start_end(env,line)) == -1)
				return (exit_parsing(&line, -2, env));
		}
		else if (env->parse->index == 0 && is_ant_nb(line) != -1)
		{
			if ((if_ant(env,line)) == -1)
				return (exit_parsing(&line, -3, env));
		}
		else if (env->parse->index == 1)
		{
			if ((if_room(env,line)) == -1)
				return (exit_parsing(&line, -4, env));
		}
		else if (env->parse->index == 2 && is_tunnel(line, env->rm_lst, 1) != -1)
		{
			if ((if_tunnel(env,line)) == -1)
				return (exit_parsing(&line, -5, env));
		}
		else
			return (exit_parsing(&line, -6, env));
		ft_memdel((void**)&line);
	}
	return (exit_parsing(&line, 0, env));
}
