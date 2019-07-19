/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:16:20 by abinois           #+#    #+#             */
/*   Updated: 2019/06/20 15:35:59 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	check_first_flagz(const char *fmt, t_flag *flagz, int *i)
{
	if (fmt[*i] == '0')
		F->zer = F->minus ? false : true;
	else if (fmt[*i] == '-')
	{
		F->minus = true;
		F->zer = false;
	}
	else if (fmt[*i] == ' ')
		F->sp = true;
	else if (fmt[*i] == '+')
	{
		F->plus = true;
		F->sp = false;
	}
	else if (fmt[*i] == '#')
		F->hash = true;
	(*i)++;
}

void	check_l_flagz(const char *fmt, t_flag *flagz, int *i)
{
	if (fmt[*i] == 'L')
	{
		F->bigl = true;
		(*i)++;
	}
	else if (fmt[*i] == 'l')
	{
		F->l = true;
		(*i)++;
		if (fmt[*i] == 'l')
		{
			F->l = false;
			F->ll = true;
			(*i)++;
		}
	}
}

void	check_bh_flagz(const char *fmt, t_flag *flagz, int *i)
{
	if (fmt[*i] == 'b')
	{
		F->b = true;
		(*i)++;
	}
	if (fmt[*i] == 'h')
	{
		F->h = true;
		(*i)++;
		if (fmt[*i] == 'h')
		{
			F->h = false;
			F->hh = true;
			(*i)++;
		}
	}
}

void	check_f_p(const char *fmt, t_flag *flagz, int *i, va_list ap)
{
	int		tmp;

	tmp = 0;
	if (fmt[*i] == '*' && (*i)++)
		tmp = va_arg(ap, int);
	else if (fmt[*i] >= '0' && fmt[*i] <= '9')
	{
		tmp = ft_atoi(fmt + *i);
		while (fmt[*i] >= '0' && fmt[*i] <= '9')
			(*i)++;
	}
	F->field = tmp < 0 ? 0 : tmp;
	if (fmt[*i] == '.' && (F->dot = true))
	{
		if (fmt[++(*i)] == '*' && (*i)++)
			tmp = va_arg(ap, int);
		else if (fmt[*i] >= '0' && fmt[*i] <= '9')
		{
			tmp = ft_atoi(fmt + *i);
			while (fmt[*i] >= '0' && fmt[*i] <= '9')
				(*i)++;
		}
		F->preci = tmp < 0 ? 0 : tmp;
		F->dot = tmp < 0 ? false : F->dot;
	}
}

char	*check_all(const char *fmt, t_flag *flagz, int *i, va_list ap)
{
	reset_flagz(F);
	while ((fmt[*i] == '0' || fmt[*i] == '-' || fmt[*i] == ' ' || fmt[*i] == '+'
		|| fmt[*i] == '#') && fmt[*i])
		check_first_flagz(fmt, F, i);
	check_f_p(fmt, F, i, ap);
	while ((fmt[*i] == 'L' || fmt[*i] == 'l' || fmt[*i] == 'b'
		|| fmt[*i] == 'h') && fmt[*i])
	{
		check_l_flagz(fmt, F, i);
		check_bh_flagz(fmt, F, i);
	}
	return (check_conv1(fmt, *F, i, ap));
}
