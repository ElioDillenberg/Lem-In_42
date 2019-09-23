/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tunnel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:59:34 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/17 18:28:48 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>

int			init_tu_tab(t_tunnel ***tu_tab, int *nt_rm)
{
	int	i;
	int nb;

	nb = nt_rm[1];
	i = 0;
	if (!(*tu_tab = (t_tunnel **)ft_memalloc(sizeof(t_tunnel*) * nb)))
		return (-1);
	while (i < nt_rm[1])
		if (!((*tu_tab)[i++] = (t_tunnel*)ft_memalloc(sizeof(t_tunnel) * nb)))
			return (-1);
	return (0);
}

static int	check_tunnel(char *line, int opt, int i)
{
	if (line[i] == '\0' && opt == 1)
		return (-2);
	if (line[i] == '-')
		line[i] = '\0';
	else
		return (-1);
	return (1);
}

static int	check_tunnel_name(char *line, t_env *env, size_t *cmp, int step)
{
	int i;

	i = 0;
	if (step == 1)
	{
		while (i < env->nt_rm[1])
		{
			if (ft_strcmp(line, env->rm_tab[i]->name) == 0)
			{
				*cmp = (*cmp) + 1;
				env->rm_tab[i]->nb_dad++;
				break ;
			}
			i++;
		}
		return (*cmp != 1 ? -2 : 1);
	}
	while (i < env->nt_rm[1])
	{
		if (ft_strcmp(line, env->rm_tab[i]->name) == 0)
		{
			*cmp = (*cmp) + 1;
			break ;
		}
		i++;
	}
	return (*cmp != 2 ? -2 : 1);
}

int			is_tunnel(char *line, t_env *env, int opt)
{
	size_t	i;
	size_t	cmp;

	i = 0;
	cmp = 0;
	if (!env->parse->is_build && build_room_tab(env) == -1)
		return (-1);
	while (line[i] != '-' && line[i] != '\0')
		i++;
	if (check_tunnel(line, opt, i) != 1)
		return (check_tunnel(line, opt, i));
	if (env->parse->index == 2 && check_tunnel_name(line, env, &cmp, 1) == -2)
		return (-2);
	line[i] = '-';
	while (*line != '-' && *line != '\0')
		line++;
	if (*line == '-')
		line++;
	else
		return (-1);
	if (env->parse->index == 2 && check_tunnel_name(line, env, &cmp, 2) == -2)
		return (-2);
	return (0);
}
