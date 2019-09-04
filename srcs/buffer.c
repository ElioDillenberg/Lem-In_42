/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <thallot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 10:28:20 by thallot           #+#    #+#             */
/*   Updated: 2019/09/04 11:45:08 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

int		strcat_big(char *src, char **dest, t_env *env)
{
	int i;
	int index;
	int len;

	i = -1;
	index = env->buffer_len;
	len = ft_strlen(src) + 1;
	env->map_len += len;
	if (index + len > BUF_SIZE)
	{
		env->tmp = *dest;
		if (!(*dest = ft_strjoin(env->tmp, env->buffer)))
			return (0);
		ft_memdel((void **)&(env)->tmp);
		reset_buffer(env);
		index = env->buffer_len;
	}
	while (src[++i])
		env->buffer[index + i] = src[i];
	env->buffer[index + i] = '\n';
	env->buffer[index + i + 1] = '\0';
	env->buffer_len += i + 1;
	return (1);
}

void	reset_buffer(t_env *env)
{
	int i;

	i = 0;
	while (i <= BUF_SIZE)
	{
		env->buffer[i] = '\0';
		i++;
	}
	env->buffer_len = 0;
}

t_env	*check_buffer(t_env *env, char **dest)
{
	if (env->buffer[0] != '\0')
	{
		env->tmp = *dest;
		*dest = ft_strjoin(env->tmp, env->buffer);
		ft_memdel((void **)&(env)->tmp);
	}
	return (env);
}
