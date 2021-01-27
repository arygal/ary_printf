/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_head.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:02:27 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 18:54:24 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		prec_proc(int zero, int dot, int prec)
{
	int		ret;

	ret = 0;
	while(prec - dot > 0)
	{
		if(zero > 0)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		--prec;
		++ret;
	}
	return(ret);
}

int		str_print(int len, char *line)
{
	int		ret;

	ret = 0;
	while( ret < len && line[ret] != '\0')
		write(1 ,&line[ret++], 1);
	return(ret);
}

int		prec_print(char	*line,t_flag *flag,int len)
{
	int ret;

	ret = 0;
	if (flag->prec >= 0)
		ret = prec_proc(0, len, flag->prec) + str_print(flag->prec, line);
	else
		ret = str_print(len, line);
	return(ret);
}

char	*ptr_proc(unsigned long long hex,int ct)
{
	unsigned long long	hex2;
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
	ret = malloc (1 + ct);
	if (!ret)
		return(0);
	ret[ct--] = '\0';
	while (hex2 != 0)
	{
		if ((hex2 % 16) < 16)
			ret[ct] = (hex2 % 16) + 48;
		else
			ret[ct--] = (hex2 % 16) + 87;
		hex2 = hex2 / 16;
	}
	return (ret);
}

int		ptr_print(char *line, t_flag *flag, int ln)
{
	int		ret;

	ret = 2;
	write(1, "0x", 2);
	if (flag->prec >= 0)
		ret = ret + prec_proc(1, ln, flag->prec) + str_print(flag->prec, line);
	else
		ret = ret + str_print(ln, line);
	return(ret);	
}