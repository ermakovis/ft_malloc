#include "malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	if (!(ptr = malloc(total_size)))
		return (NULL);
	bzero(ptr, total_size);
	return (ptr);
}
