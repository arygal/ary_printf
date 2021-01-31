/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:59:51 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 23:45:06 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static  t_flag  flag_init(t_flag flag)
{
    flag.minus = 0;
    flag.zero = 0;
    flag.prec = -1;
    flag.star = 0;
    flag.width = 0;
    flag.type = 0;
    return(flag);
}


static  int     proc_line(va_list   arg, const char *line)
{  
    t_flag flag;
    int     ret;  // return is nuber of chars printed
    int     pos;

    ret = 0;
    pos = 0;
    while (1)
    {
        if(line[pos] == '\0')
            break;
        flag = flag_init(flag);
        if (line[pos] == '%' && line[pos + 1] != '\0')
            {
                pos = flag_parse(&flag ,line , pos + 1 , arg);
                if (ft_strchr("cspdiuxX%", line[pos]))
                    ret = ret + conversion_parse(&flag, arg);
                else if (line[pos] != '\0')
                    ret = ret + write(1, &line[pos], 1);
            }
        else
           ret = ret + write(1, &line[pos], 1);
        ++pos;
    }
    return(ret);
}

int ft_printf(const char *line, ...)
{
    int     ret;
    va_list arg;
 //   const char  *temp;

    ret = 0;
    
 //   temp = ft_strdup(line);
  //  if (!temp)
  //      return(NULL);
    va_start(arg, line);
 //   ret = proc_line(arg, temp);
    ret = proc_line(arg, line);
    va_end(arg);
 //   free(temp);
    return(ret);
}
