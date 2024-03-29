/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:59:49 by megen             #+#    #+#             */
/*   Updated: 2021/01/31 16:57:29 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF_H
# define __FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_flag
{
	int			minus;
	int			zero;
	int			prec;
	int			star;
	int			width;
	int			type;
}				t_flag;

int				ft_printf(const char *line, ...);
int				conversion_parse(t_flag *flag, va_list arg);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
int				flag_parse(t_flag *flag, const char *line,
							int pos, va_list arg);
int				prec_proc(int zero, int dot, int prec);
size_t			ft_strlen(const char *s);
int				str_print(int len, char *line);
int				prec_print(char *line, t_flag *flag, int len);
char			*ptr_proc(unsigned long long hex, int ct);
int				ptr_print(char *line, t_flag *flag, int len);
char			*ft_itoa(long int n);
int				int_proc(char *ptr, t_flag *flag, int i, int len);
int				conv_to_uns_int(unsigned int i, t_flag *falg);
char			*ft_uitoa(unsigned int n);
int				uns_int_proc(char *ptr, t_flag *flag, int len);
int				conv_to_hex(unsigned int hex, t_flag *flag, int c);
char			*hex_to_str(unsigned int hex, int ct);
int				ft_toupper(int c);
int				hex_proc(char *ptr, t_flag *flag, int len);
int				conv_to_per(t_flag *flag);

#endif
