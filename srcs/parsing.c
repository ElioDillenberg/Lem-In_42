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
	ft_memdel((void**)line);
	get_next_line(0, line, 0);
	env->ret = ret;
	return (env->ret);
}

/*
**
**
*/

int parsing(t_env *env)
{
	char	*line;
	int		start_end[2];
	int		index;
	int		command;
	int		ret;

	line = NULL;
	start_end[0] = 0;
	start_end[1] = 0;
	command = 0;
	index = 0;
	while ((ret = get_next_line(0, &line, 1)) && ret != -1 && ret != 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			if (start_end[0] == 1 || start_end[1] == 1)
				return (exit_parsing(&line, 0, env));
			if (!(env->to_print = ft_strjoinlemin(&(env)->to_print, &line, 1)))
				return (exit_parsing(&line, -1, env));
		}
		else if (line[0] == '#' && line[1] == '#')
		{
			if (get_command(line, start_end) == -1)
				return (exit_parsing(&line, 0, env));
			if (!(env->to_print = ft_strjoinlemin(&(env)->to_print, &line, 1)))
				return (exit_parsing(&line, -1, env));
		}
		else if (index == 0 && is_ant_nb(line) != -1)
		{
			if (start_end[0] == 1 || start_end[1] == 1)
				return (exit_parsing(&line, 0, env));
			env->nt_rm[0] = ft_atoui(line);
			if (!(env->to_print = ft_strjoinlemin(&(env)->to_print, &line, 1)))
				return (exit_parsing(&line, -1, env));
			index++;
		}
		else if (index == 1)
		{
			if (is_room(line, env->rm_lst) != -1)
			{
				if (add_room(line, env->rm_lst, start_end) == -1)
					return (exit_parsing(&line, -1, env));
				if (!(env->to_print = ft_strjoinlemin(&(env)->to_print, &line, 1)))
					return (exit_parsing(&line, -1, env));
			}
			else if (is_tunnel(line, env->rm_lst) != -1)
			{
				if (start_end[0] == 1 || start_end[1] == 1)
					return (exit_parsing(&line, 0, env));
				if (!(env->nt_rm[1] = build_room_tab(env->rm_lst, &(env)->rm_tab)))
					return (exit_parsing(&line, -1, env));
				if (init_tu_tab(&(env)->tu_tab, env->nt_rm) == -1)
					return (exit_parsing(&line, -1, env));
				get_tunnel(env, line);
				index++;
				if (!(env->to_print = ft_strjoinlemin(&(env)->to_print, &line, 1)))
					return (exit_parsing(&line, -1, env));
			}
			else
				return (exit_parsing(&line, 0, env));
		}
		else if (index == 2 && is_tunnel(line, env->rm_lst) != -1)
		{
			if (start_end[0] == 1 || start_end[1] == 1)
				return (exit_parsing(&line, 0, env));
			get_tunnel(env, line);
			if (!(env->to_print = ft_strjoinlemin(&(env)->to_print, &line, 1)))
				return (exit_parsing(&line, -1, env));
		}
		else
			return (exit_parsing(&line, 0, env));
		ft_memdel((void**)&line);
	}
	return (exit_parsing(&line, 0, env));
}
