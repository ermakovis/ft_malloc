#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*ret;

	malloc_log(LOG_BRIEF, "Realloc called for %d ptr of size %d", \
		ptr, size);
	if (!ptr)
		return (malloc(size));
	block = ptr - sizeof(t_block);
	if (block->size >= size)
		return (ptr);
	if (!(ret = malloc(size)))
		return (NULL);
	free(ptr);
	return (ret);
}
