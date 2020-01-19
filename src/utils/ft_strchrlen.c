#include "malloc.h"

int		ft_strchrlen(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (!s[i])
			return (-1);
		i++;
	}
	return (i);
}
