#include "ft_malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*ret;

	if (!ptr)
		return (malloc(size));
	block = (t_block*)ptr - 1;
	//TODO SPLIT
	if (block->size >= size)
		return (ptr);
	if (!(ret = malloc(size)))
		return (NULL);
	free(ptr);
	return (ret);
}
