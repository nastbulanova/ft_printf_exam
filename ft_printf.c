#include "ft_printf.h"

int ft_putchr(char  c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char *str)
{
    int len;

    if (!str)
		str = "(null)";
    len = 0;
    while (str && *str)
    {
        len += ft_putchr(*str);
        str++;
    }
    return (len);
}

int ft_putnbr_base(long long nbr, char *base, int size)
{
    int len;
    char c;

    len = 0;
    if (nbr < 0)
    {
        ft_putchr('-');
        nbr = nbr * (-1);
        len++;
    }
    if (nbr >= size)
        len += ft_putnbr_base(nbr/size, base, size);
    c = base[nbr%size];
    len += ft_putchr(c);
    return(len);
}

int ft_putnbr(int type, long long nbr)
{
    int len;
    int size;
    char *base;

    len = 0;
    if (type == 1)
    {
        base = "0123456789";
        size = 10;
    }
    else
    {
        base = "0123456789abcdef";
        size = 16;
    }
    len = ft_putnbr_base(nbr, base, size);
    return (len);
}

int ft_printf(const char *format, ... )
{
    va_list arg;
    int     len;

    va_start(arg, format);
    len = 0;
    while(format && *format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'd')
                len+=ft_putnbr(1, (long long)va_arg(arg, int));
            else if (*format == 'x')
                len+=ft_putnbr(2, (long long)va_arg(arg, unsigned int));
            else if (*format == 's')
                len+=ft_putstr(va_arg(arg, char *));
            else
            {
                len+=ft_putchr('%');
                len+=ft_putchr(*format);
            }
        }
        else
            len+=ft_putchr(*format);
        format++;
    }
    va_end(arg);
    return(len);
}

int main(void)
{
    int num = 42;
    char *str = "ola mundio";
    char *str1 = NULL;
    unsigned int hex = 0xAABBCCDD;

    printf("printf: \n");
    printf("num: %d\nstr: %s\nhex: %x\n", num, str, hex);
    printf("ft_printf: \n");
    ft_printf("num: %d\nstr: %s\nhex: %x\n", num, str1, num);
    return (0);
}