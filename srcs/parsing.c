/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 11:38:10 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/25 18:47:36 by edillenb         ###   ########.fr       */
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
	if (env->parse->index < 2 || (env->parse->start_end[0] != 2
		|| env->parse->start_end[1] != 2))
		ft_putendl("[ERROR : Missing information to process]");
	if (*line && ret == -2)
	{
		if (*line && ft_printf("[ERROR at line : %s]\n", *line) == -1)
		{
			ft_memdel((void**)line);
			get_next_line(0, line, 0, 0);
			return (-1);
		}
	}
	else if (ret == -1)
		ft_putendl("[MALLOC ERROR]\n");
	ft_memdel((void**)line);
	get_next_line(0, line, 0, 0);
	env->parse->ret = ret;
	return (ret);
}

int			parsing_core(t_env *env, char *line)
{
	int ret;

	if (line[0] == '#')
	{
		if (line[1] != '#' && (ret = if_comment(env, line, 1)) < 0)
			return (ret);
		else if (line[1] == '#' && (ret = if_start_end(env, line)) < 0)
			return (ret);
	}
	else if (env->parse->index == 0)
	{
		if ((ret = if_ant(env, line)) < 0)
			return (ret);
	}
	else if (env->parse->index == 1)
	{
		if ((ret = if_room(env, line)) < 0)
			return (ret);
	}
	else if (env->parse->index == 2 && is_tunnel(line, env->rm_lst, 1, 0) != -1)
	{
		if ((ret = if_tunnel(env, line)) < 0)
			return (ret);
	}
	return (1);
}

static int	is_number(char *line)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0' || i == 0)
		return (0);
	return (1);
}

static int	check_file(t_env *env, char *line)
{
	int i;

	i = 0;
	if (line[0] == '#')
	{
		if ((if_comment(env, line, 0)) == -1)
			return (-1);
		if ((get_command(line, env->parse->start_end)) != -0)
			return (-1);
	}
	else if (!is_number(line))
		return (-1);
	return (1);
}

int			parsing(t_env *env)
{
	char	*line;
	int		ret;

	line = NULL;
	if (env->opt_file_path)
		env->parse->fd = open(env->opt_file_path, O_RDONLY);
	else
		env->parse->fd = 0;
	while ((env->parse->ret = get_next_line(env->parse->fd, &line, 1, 0))
			&& env->parse->ret != -1 && env->parse->ret != 0)
	{
		if (env->parse->index == 0 && (check_file(env, line)) == -1)
			return (exit_parsing(&line, -2, env));
		if ((ret = parsing_core(env, line)) < 0)
			return (exit_parsing(&line, ret, env));
		ft_memdel((void**)&line);
	}
	return (exit_parsing(&line, 0, env));
}
