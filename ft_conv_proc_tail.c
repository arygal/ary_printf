/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_proc_tail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:30:06 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 23:10:22 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_to_uns_int(unsigned int i, t_flag *flag)
{
	int		ret;
	char	*ptr;
	int		len;

	ret = 0;
	//i = (unsigned int)(4294967295 + 1 + i); //dunno
	if (flag->prec == 0 && i == 0)
		return(prec_proc(0, 0, flag->width));
	ptr = ft_uitoa(i);
	if(!ptr)
		return(ret);
	len = (int)ft_strlen(ptr);
	ret = uns_int_proc(ptr, flag, len);
	free(ptr);
	return(ret);
}

int		conv_to_hex(unsigned int hex, t_flag *flag, int c)
{
	int		ret;
	char	*ptr;
	int		ct;
	int		len;

	ret = 0;
	//hex = (unsigned int)(4294967295 + 1 + hex); //dunno
	if (flag->prec == 0 && hex == 0)
		return(prec_proc(0 ,0 , flag->width));
	ptr = hex_to_str(hex, ct);
	if(!ptr)
		return(ret);
	len =(int)ft_strlen(ptr);
	ct = len;
	if (c == 1)
		while (--ct > 0)
			ptr[ct] = ft_toupper(ptr[ct]);
	ret = hex_proc(ptr, flag, len);
	free(ptr);
	return(ret);
}