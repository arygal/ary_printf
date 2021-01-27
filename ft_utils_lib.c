/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_lib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 23:46:21 by megen             #+#    #+#             */
/*   Updated: 2021/01/27 23:53:25 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return ((void *)0);
		s++;
	}
	return ((char*)s);
}

static	char	*ft_itoa_charset(char *ret, long int nclone, int size)
{
	while (size >= 0)
	{
		ret[size--] = nclone % 10 + 48;
		nclone = nclone / 10;
	}
	return (ret);
}

char			*ft_itoa(int n)
{
	long int	nclone;
	int			size;
	char		*ret;

	nclone = n;
	size = 0;
	while (nclone != 0)
	{
		nclone = nclone / 10;
		size++;
	}
	if (n <= 0)
		size++;
	if (!(ret = malloc(size)))
		return ((void *)0);
	ret[size] = '\0';
	nclone = n;
	if (nclone < 0)
	{
		ret = ft_itoa_charset(ret, nclone * -1, size - 1);
		ret[0] = 45;
	}
	else
		ret = ft_itoa_charset(ret, nclone, size - 1);
	return (ret);
}

char			*ft_strdup(const char *s1)
{
	int		lenchar;
	char	*malchar;

	lenchar = ft_strlen(s1);
	malchar = malloc(lenchar + 1);
	if (malchar == (void *)0)
		return (malchar);
	while (lenchar >= 0)
	{
		malchar[lenchar] = s1[lenchar];
		--lenchar;
	}
	return (malchar);
}

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		return (c - 32);
	return (c);
}
