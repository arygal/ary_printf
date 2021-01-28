/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_porc_head.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:30:02 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 20:30:03 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		conv_to_c(char c, t_flag *flag)
{
	int ret;

	ret = 0;
	if (flag->minus == 1)
		write(1, &c, 1);
	ret = prec_proc(0, 1, flag->prec) + 1;
	if (flag->minus == 0)
		write(1, &c, 1);
	return (ret);
}

static int		conv_to_str(char *line, t_flag *flag)
{
	int ret;
	int len;

	ret = 0;
	if (!line)
		line = "(null)";
	len = (int)ft_strlen(line);
	if (flag->prec >= 0 && flag->prec > len)
		flag->prec = len;
	if (flag->minus == 1)
		ret = prec_print(line, flag, len);
	if (flag->prec >= 0)
		ret = ret + prec_proc(0, flag->prec, flag->width);
	else
		ret = ret + prec_proc(0, len, flag->width);
	if (flag->minus == 0)
		ret = ret + prec_print(line, flag, len);
	return(ret);
}

static int		conv_to_ptr(unsigned long long targ, t_flag *flag)
{
	char	*ptr;
	int		ret;
	int		ct;
	int		len;

	ct = 0;
	ret = 0;
	if (targ == 0 && flag->prec == 0)
		{
			write(1, "0x", 2);
			return(prec_proc(1, 0, flag->width) + 2);
		}
	ptr = ptr_proc(targ, ct);
	if(!ptr)
		return(ret);
	len = (int)ft_strlen(ptr);
	if (flag->prec < len)
		flag->prec = len;
	if (flag->minus == 1)
		ret = ptr_print (ptr, flag, len);
	ret = ret + prec_proc(0, 2 + len, flag->width);
	if (flag->minus == 0)
		ret = ret + ptr_print (ptr, flag, len);
	free(ptr);
	return(ret);
}

static int		conv_to_int(int i, t_flag *flag)
{
	char	*ptr;
	int		i2;
	int		ret;

	i2 = i;
	ret = 0;
	
	if (i == 0 && flag->prec == 0)
		return(prec_proc(0, 0, flag->width));
	if (i < 0 && (flag->zero == 1 || flag->prec >= 0))
	{
		if (flag->zero == 1 && flag->prec ==-1)
			write(1, "-" ,1);
		flag->zero = 1;
		--flag->width;
		++ret;
	}
	ptr = ft_itoa(i);
	if (!ptr)
		return(ret);
	ret = ret + int_proc(ptr, flag, i2);
	free(ptr);
	return(ret);
}

int 			conversion_parse(t_flag *flag, va_list arg)
{
	int		ret; //cspdiuxX%

	ret = 0;
	if (flag->type == 'c')
		ret = conv_to_c(va_arg(arg, int), flag);
	else if (flag->type == 's')
		ret = conv_to_str(va_arg(arg, char *), flag);
	else if (flag->type == 'p')
		ret = conv_to_ptr(va_arg(arg, unsigned long long), flag);
	else if (flag->type == 'd' || flag->type == 'i')
		ret = conv_to_int(va_arg(arg, int), flag);
	else if (flag->type == 'u')
		ret = conv_to_uns_int(va_arg(arg, unsigned int), flag);
	else if (flag->type == 'x')
		ret = conv_to_hex(va_arg(arg, unsigned int), flag, 0);
	else if (flag->type == 'X')
		ret = conv_to_hex(va_arg(arg, unsigned int), flag, 1);
	else
		ret = conv_to_per(flag);
	return (ret);
}
