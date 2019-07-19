/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:14:02 by edillenb          #+#    #+#             */
/*   Updated: 2019/06/20 15:29:55 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char		*m_to_buf(int *m, char *buf, const char *fmt, int i)
{
	char	*tmpsub;
	char	*tmpjoin;

	if (!buf && !(buf = ft_strnew(0)))
		return (NULL);
	if (*m)
	{
		if (!(tmpsub = ft_strsub(&fmt, i - *m, *m, 0)))
		{
			ft_memdel((void**)&buf);
			return (NULL);
		}
		if (!(tmpjoin = ft_strjoinfr(&buf, &tmpsub, 3)))
			return (NULL);
		*m = 0;
		return (tmpjoin);
	}
	return (buf);
}

char		*arg_to_buf(char **buf, char **arg)
{
	char	*tmpjoin;

	if (!(*buf) && (!(*buf = ft_strnew(0))))
	{
		ft_memdel((void**)arg);
		return (NULL);
	}
	if (!(tmpjoin = ft_strjoinfr(buf, arg, 3)))
		return (NULL);
	return (tmpjoin);
}

int			print_return(va_list ap, char **buf)
{
	int		rv;
	int		x;

	rv = return_value(*buf);
	x = ft_strlen(*buf);
	reput_backzer(buf);
	put_color(*buf, x, -1);
	ft_memdel((void**)buf);
	va_end(ap);
	return (rv);
}

static int	printf_algo(va_list ap, const char *fmt, int *im, char **buf)
{
	char	*arg;
	t_flag	flagz;

	while (fmt[im[0]])
		if (fmt[im[0]++] == '%')
		{
			if (!(*buf = m_to_buf(&(im[1]), *buf, fmt, im[0] - 1)))
				return (-1);
			if (im[1] == 0)
			{
				if (!(arg = check_all(fmt, &F, &(im[0]), ap)))
					return (-1);
				if (!(*buf = arg_to_buf(buf, &arg)))
					return (-1);
			}
			else
				im[1] = 0;
		}
		else
			im[1]++;
	if (!(*buf = m_to_buf(&(im[1]), *buf, fmt, im[0])))
		return (-1);
	return (0);
}

int			ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*buf;
	int		im[2];

	buf = NULL;
	im[0] = 0;
	im[1] = 0;
	g_fd = 1;
	va_start(ap, fmt);
	if (printf_algo(ap, fmt, im, &buf) == -1)
	{
		va_end(ap);
		return (-1);
	}
	return (print_return(ap, &buf));
}
