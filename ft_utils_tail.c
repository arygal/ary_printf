/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_tail.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:22:25 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 23:29:57 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*hex_to_str(unsigned int hex, int ct)
{
	unsigned int		hex2;
	char				*ret;

	hex2 = hex;
	ct = 0;
	if (hex == 0)
		return(ft_strdup("0"));
	while (hex != 0)
	{
		hex = hex / 16;
		++ct;
	}
	ret = malloc(1 + ct);
	if (!ret)
		return(0);
	ret[ct--] = '\0';
	while (hex2 != 0)
	{
		if ((hex2 % 16) < 10)
			ret[ct] = (hex2 % 16) + 48;
		else
			ret[ct--] = (hex2 % 16) + 87;
		hex2 = hex2 / 16;
	}
	return (ret);
}

static	int		hex_print(char *ptr, t_flag *flag, int len)
{
	int		ret;

	ret = 0;
	if (flag->prec >= 0)
		ret = prec_proc(1, len - 1, flag->prec - 1);
	return(ret + str_print(len, ptr));
}

int				hex_proc(char *ptr, t_flag *flag, int len)
{
	int		ret;

	ret = 0;
	if (flag->minus == 1)
		ret = hex_print(ptr, flag, len);
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
		ret = ret + hex_print(ptr, flag, len);
	return(ret);
}

int				conv_to_per(t_flag *flag)
{
	int		ret;

	ret = 1;
	if (flag->minus == 1)
		write (1, "%", 1);
	ret = ret + prec_proc(flag->zero, 1 , flag->width);
	if (flag->minus == 0)
		write (1, "%", 1);
	return(ret);
}
