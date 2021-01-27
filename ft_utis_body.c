/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utis_body.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:50:30 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 22:08:55 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	int_print(char *ptr, t_flag *flag, int i, int len)
{
	int		ret;

	ret = 0;
	if (i < 0 && flag->prec >= 0)
		write(1, '-', 1);
	if (flag->prec >= 0)
		ret =  ret + prec_proc(1, len - 1, flag->prec - 1);
	ret = ret + str_print(len, ptr);
	return(ret);
}

int		int_proc(char *ptr, t_flag *flag, int i)
{
	int		ret;
	int		len;

	len = (int)ft_strlen(ptr);
	ret = 0;
	if (flag->minus == 1)
		ret = int_print(ptr, flag, i, len);
	if (flag->prec >= 0 && flag->prec < len)
		flag->prec = len;
	if (flag->prec >= 0)
	{
		flag->width = flag->width - flag->prec;
		ret = ret + prec_proc(0, 0, flag->width);
	}
	else
		ret = ret +	prec_proc(flag->zero, len, flag->width);
	if (flag->minus == 0)
		ret = ret + int_print(ptr, flag, i, len);
	return(ret);
}

char			*ft_uitoa(unsigned int n)
{
	unsigned int	nclone;
	int				size;
	char			*ret;

	nclone = n;
	size = 0;
	while (nclone != 0)
	{
		nclone = nclone / 10;
		size++;
	}
	if (n = 0)
		size++;
	if (!(ret = malloc(size + 1)))
		return ((void *)0);
	ret[size--] = '\0';
	while (size >= 0)
	{
		ret[size--] = n % 10 + 48;
		n = n / 10;
	}
	return (ret);
}

static int		uns_int_print(char *ptr,t_flag *flag, int len)
{
	int			ret;

	ret = 0;
	if (flag->prec >= 0)
		ret = prec_proc(1, len - 1, flag->prec - 1);
	return( ret + str_print(len, ptr));
}

int				uns_int_proc(char *ptr, t_flag *flag, int len)
{
	int			ret;

	ret = 0;
	if (flag->minus == 1)
		ret = uns_int_print(ptr, flag, len);
	if (flag->prec < len && flag->prec >= 0)
		flag->prec = len;
	if (flag->prec >= 0)
		{
			flag->width = flag->width - flag->prec;
			ret = ret + prec_proc(0, 0, flag->width);
		}
	else
		ret = ret + prec_proc(flag->zero, len, flag->width);
	if (flag->minus == 0)
		ret = ret + uns_int_print(ptr, flag, len);
	return(ret);
}