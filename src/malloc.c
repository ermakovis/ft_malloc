#include "ft_malloc.h"

static void *malloc_small(size_t size)
{
	t_block	*ret;
	t_zone	*zone;

	size = (size + 15) & ~15;
	if (find_zone(&zone, size) == EXIT_FAILURE)
		return (NULL);
	if (find_block(&ret, zone, size) == EXIT_SUCCESS)
		return (ret + 1);
	return (NULL);
}

static void *malloc_large(size_t size)
{
	t_block	*ret;

	size = (size + 15) & ~15;
	if (!(ret = malloc_mmap(size + sizeof(t_block))))
		return (NULL);
	ret->size = size;
	ret->free = 0;
	ret->prev = 0;
	ret->next = g_malloc->large;
	if (g_malloc->large)
		g_malloc->large->prev = ret;
	g_malloc->large = ret;
	return (ret + 1);
}

void	*malloc(size_t size)
{
	write (1, "my - ", 5);
	if (init_malloc() == EXIT_FAILURE)
		return (NULL);
	if (size <= MALLOC_SMALL)
		return (malloc_small(size));
	return (malloc_large(size));
}
