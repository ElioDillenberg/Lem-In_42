/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:30:01 by edillenb          #+#    #+#             */
/*   Updated: 2019/09/02 19:30:03 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lem_in.h"
#include "../libft/libft.h"

void       result(t_env *env)
{
    t_path  *cr;

    cr = env->path_lst[env->cr_path];
    if (env->cr_path == 0)
        return;
}