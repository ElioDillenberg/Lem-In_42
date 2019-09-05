/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:04:03 by thallot           #+#    #+#             */
/*   Updated: 2019/09/03 16:49:41 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

/*
   Affiche la liste de tunnels pour voir si ils sont bien bouché
   */

// void view_tunnel_by_name(t_env *env)
// {
// 	int i = 0;
// 	int j = 0;

// 	while (i < env->nt_rm[1])
// 	{
// 		j = 0;
// 		ft_printf("Salle [%s] connecté à : ", env->rm_tab[i]->name);
// 		while (j < env->nt_rm[1])
// 		{
// 			if (env->tu_tab[i][j])
// 				ft_printf(" %s ", env->rm_tab[j]->name);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// }

// char	*ft_joinfree(char *s1, char *s2)
// {
// 	char *tmp;

// 	tmp = s1;
// 	if (!(s1 = ft_strjoin(s1, s2)))
// 		return (NULL);
// 	ft_memdel((void **)&tmp);
// 	return (s1);
// }

// char	*ft_strrev(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	ch;

// 	if (!str || !*str)
// 		return (str);
// 	i = strlen(str) - 1;
// 	j = 0;
// 	while (i > j)
// 	{
// 		ch = str[i];
// 		str[i] = str[j];
// 		str[j] = ch;
// 		i--;
// 		j++;
// 	}
// 	return (str);
// }

// char	*ft_strndup(const char *s1, size_t n)
// {
// 	size_t	i;
// 	char	*dest;

// 	if (!(dest = (char *)malloc(sizeof(*dest) * n + 1)))
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0' && i < n)
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// void print_lst(t_env *env)
// {
// 	t_room *room;

// 	room = (*env->rm_lst_path);
// 	ft_printf("Room : ");
// 	while (room)
// 	{
// 		ft_printf("%s ", room->name);
// 		room = room->next;
// 	}
// 	ft_printf("\n");
// }
