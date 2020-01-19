#include "malloc.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char *p;

	p = s;
	while (n-- > 0)
		*p++ = '\0';
	return (s);
}
