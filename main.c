#include "ft_printf.h"
#include "stdio.h"

int main()
{
    char test[ ] = "Hello world!";
    int test2 = 1234567890;
    unsigned int test3 = 4294967295;
    unsigned int hex = 140;
    char    *ptr;
    char c = 'c';

    ptr = malloc(1);
    ft_printf("testSTR:%s\n", test);
    ft_printf("testDEC:%d\n", test2);
    ft_printf("testUI:%u\n", test3);
    ft_printf("testHEX:%X\n", hex);
    ft_printf("testC:%c\n", c);
    ft_printf("testPTR:%p\n", ptr);

    printf("BasePTR:%p\n", ptr);
    return(0);
}
