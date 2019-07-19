/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:30:34 by edillenb          #+#    #+#             */
/*   Updated: 2019/04/12 18:30:53 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>

void	ft_display_file(char *file_name)
{
	int		file_des;
	int		ret;
	char	buf[1];

	if (!file_name)
		return ;
	file_des = open(file_name, O_RDONLY);
	while ((ret = read(file_des, buf, 1)) && ret != -1)
		write(1, buf, 1);
}
