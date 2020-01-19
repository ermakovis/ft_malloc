#include "malloc.h"

static void	malloc_print_sizet(size_t num)
{
	char	ch;

	if (num > 9)
	{
		malloc_print_sizet(num / 10);
		malloc_print_sizet(num % 10);
	}
	else
	{
		ch = num + '0';
		write(1, &ch, 1); 
	}
}

static int	malloc_log_format(const char *format)
{
	int		len;

	if (!(len = ft_strchrlen(format, '%')))
		return (0);
	if (len == -1)
		len = ft_strlen(format);
	write(1, format, len);
	return (len);
}

static int	malloc_log_argument(const char *format, va_list valist)
{
	if (format[0] != '%')
		return (0);
	if (format[1] == 'd')
		malloc_print_sizet(va_arg(valist, size_t));
	if (format[1] == 's')
		ft_putstr(va_arg(valist, char*));
	return (2);
}

static void malloc_log_cycle(va_list valist, const char *format)
{
	int		i;

	i = 0;
	while (format[i])
	{
		i += malloc_log_format(&format[i]);
		i += malloc_log_argument(&format[i], valist);
	}
}

void		malloc_log(int loglevel, const char *format, ...)
{
	va_list		valist;

	if (loglevel > g_malloc->loglevel)
		return ;
	va_start(valist, format);
	malloc_log_cycle(valist, (char*)format);
	va_end(valist);
	write(1, "\n", 1);
	return ;
}
