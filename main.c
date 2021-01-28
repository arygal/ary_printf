#include "ft_printf.h"
#include "stdio.h"

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


//-----------------------------------------------------------------------------------//

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

//--------------------------------------------------------------------------------------------------//

static int	int_print(char *ptr, t_flag *flag, int i, int len)
{
	int		ret;

	ret = 0;
	if (i < 0 && flag->prec >= 0)
		write(1, "-", 1);
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
	if (n == 0)
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



//--------------------------------------------------------------------------------------------//

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


//------------------------------------------------------------------------------------------------//

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

	ct = 0;
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

//-----------------------------------------------------------------------------------//

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

//------------------------------------------------------------------------------------------------------//

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

//---------------------------------------------------------------------------------------------------------//

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

//-----------------------------------------------------------------------------------------------------//
int main()
{
    char test[ ] = "Hello world!";
    int test2 = 55555;
    unsigned int test3 = 4294967295;
    unsigned int hex = 325;
    char    *ptr;
    char c = 'c';

    ptr = malloc(1);
    ft_printf("testSTR:%s\n", test);
    ft_printf("testDEC:%d\n", test2);
    ft_printf("testUI:%u\n", test3);
    ft_printf("testHEX:%X\n", hex);
    ft_printf("testC:%c\n", c);
    ft_printf("testPTR:%p\n", ptr);

    printf("BasePTR%p\n", ptr);
    return(0);
}
