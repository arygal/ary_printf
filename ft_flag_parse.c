/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 01:52:54 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 23:30:44 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	flag_dot (t_flag *flag, const char* line, int pos, va_list arg)
{
	++pos;
	if (line[pos] == '*')
		{
			flag->prec = va_arg(arg, int);
			++pos;
		}
	else
	{
		flag->prec = 0;
		while (line[pos] > 47 && line[pos] < 58 ) 
			flag->prec = flag->prec * 10 + (line[pos++] - 48);
		
	}
	return(pos);
}

static t_flag	*flag_minus(t_flag *flag)
{
	flag->minus = 1;
	flag->zero = 0;
	return(flag);
}

static t_flag	*flag_star(t_flag *flag, va_list arg)
{
	flag->width = va_arg(arg, int);
	flag->star = 0;
	if (flag->width < 0 )
	{
		flag->width = flag->width * -1;
		flag->minus = 1;
	}
	return(flag);
}
static t_flag	*flag_digit(int digit, t_flag *flag)
{
	if (flag->star == 1)
		flag->width = 0;
	flag->width = flag->width * 10 + digit - 48;
	return(flag);
}

int  flag_parse(t_flag *flag, const char *line, int pos, va_list arg)
{
	char	*specifier;

	specifier = (char *)&"-.*0123456789cspdiuxX%";
    while(line[pos] != '\0')
	{
		if (!ft_strchr(specifier, line[pos])) /// printf ("asdas%-.0bvbvbv")
			return(pos);
		else if (line[pos] == '0' && flag->minus == 0 & flag->width == 0)
			flag->zero = 1;
		else if (line[pos] == '.')
			pos = flag_dot(flag, line, pos, arg); /// TODO: CHEK IF IT CORRECT
		if (line[pos] == '-')
			flag = flag_minus(flag);
		if (line[pos]  == '*')
			flag = flag_star(flag, arg);
		if (line[pos] > 47 && line[pos] < 58)
			flag = flag_digit(line[pos], flag);
		else
		{
			specifier += 13;
			flag->type = (int)*ft_strchr(specifier, line[pos]); ///cspdiuxX%
			specifier -= 13;
		}
		++pos;
	}
	return(pos);
}
