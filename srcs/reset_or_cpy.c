/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_or_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:07:46 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/17 18:15:23 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

static t_path	*copy_room(t_path *pnocr)
{
	t_path	*new;

	if (!(new = (t_path*)ft_memalloc(sizeof(t_path))))
		return (NULL);
	new->nb = pnocr->nb;
	new->len = pnocr->len;
	new->index = pnocr->index;
	new->ant = pnocr->strt_ants;
	return (new);
}

static int		copy_loop(t_path **new_head, t_path **new_cr, t_path **pnocr)
{
	if (*new_head == NULL)
	{
		if (!(*new_head = copy_room(*pnocr)))
			return (-1);
		(*new_head)->tail_path = *new_head;
	}
	else
	{
		if (!(*new_cr = copy_room(*pnocr)))
			return (-1);
		(*new_head)->prev_room = *new_cr;
		(*new_cr)->next_room = *new_head;
		(*new_cr)->tail_path = (*new_head)->tail_path;
		*new_head = *new_cr;
	}
	*pnocr = (*pnocr)->prev_room;
	return (0);
}

static t_path	*copy_path_lst(t_env *env)
{
	int		not_cr;
	t_path	*new_head;
	t_path	*new_cr;
	t_path	*pnocr;

	new_head = NULL;
	new_cr = NULL;
	not_cr = env->cr_path == 0 ? 1 : 0;
	pnocr = env->path_lst[not_cr];
	while (pnocr->next_path)
		pnocr = pnocr->next_path;
	pnocr = pnocr->tail_path;
	while (pnocr)
		if (copy_loop(&new_head, &new_cr, &pnocr) == -1)
			return (NULL);
	return (new_head);
}

static int		get_last_path_lst(t_env *env)
{
	t_path	*cr;

	cr = env->path_lst[env->cr_path];
	if (!cr)
	{
		if (!(env->path_lst[env->cr_path] = copy_path_lst(env)))
			return (-1);
	}
	else
	{
		while (cr->next_path)
			cr = cr->next_path;
		if (!(cr->next_path = copy_path_lst(env)))
			return (-1);
	}
	return (0);
}

int				reset_or_cpy(t_env *env)
{
	if (env->did_cut == 1)
	{
		ft_path_lst_del(&(env->path_lst[env->cr_path]));
		env->path_lst[env->cr_path] = NULL;
		env->did_cut = 0;
		cut_and_reset(env, 1, 1);
	}
	else if (env->lf_path > 1)
	{
		if (get_last_path_lst(env) == -1)
			return (-1);
	}
	return (0);
}
