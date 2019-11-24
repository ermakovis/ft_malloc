#include "libft.h"
#include <stdarg.h>

static int	ft_pjoin_format(const char *format, char **ret)
{
	int		len;
	char	*line;
	char	*tmp;

	if (!(len = ft_strchrlen(format, '%')))
		return (0);
	if (len == -1)
		len = ft_strlen(format);
	if (!(line = ft_strndup(format, len)))
		return (0);
	if (!(tmp = ft_strjoin(*ret, line)))
		return (0);
	ft_memdel((void**)ret);
	ft_memdel((void**)&line);
	*ret = tmp;
	return (len);
}

static int	ft_pjoin_argument(const char *format, char **ret, va_list valist)
{
	char	**arg_free;
	char	*arg;
	char	*tmp;

	if (format[0] != '%')
		return (0);
	if (format[1] == 's')
		arg = va_arg(valist, char*);
	else if (format[1] == 'f')
	{
		arg_free = va_arg(valist, char**);
		arg = *arg_free;
	}
	tmp = ft_strjoin(*ret, arg);
	ft_memdel((void**)ret);
	if (format[1] == 'f')
		ft_memdel((void**)arg_free);
	*ret = tmp;
	return (2);
}

static char	*ft_pjoin_cycle(va_list valist, const char *format)
{
	int		i;
	char	*ret;

	i = 0;
	ret = 0;
	while (format[i])
	{
		i += ft_pjoin_format(&format[i], &ret);
		i += ft_pjoin_argument(&format[i], &ret, valist);
	}
	return (ret);
}

char	*ft_powerjoin(const char *format, ...)
{
	va_list		valist;
	char		*ret;

	va_start(valist, format);
	ret = ft_pjoin_cycle(valist, (char*)format);
	va_end(valist);
	return (ret);
}
