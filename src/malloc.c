#include "malloc.h"

static void *malloc_small(size_t size)
{
	t_block	*ret;
	t_zone	*zone;

	//malloc_log("Malloc_small", LOG_FULL);
	size = (size + 15) & ~15;
	if (find_zone(&zone, size) == EXIT_FAILURE)
	{
		//malloc_log("Failed to find a zone", LOG_FULL);
		return (NULL);
	}
	if (find_block(&ret, zone, size) == EXIT_SUCCESS)
		return (ret + 1);
	//malloc_log("Failed to find a block", LOG_FULL);
	return (NULL);
}

static void *malloc_large(size_t size)
{
	t_block	*ret;

	//malloc_log("Malloc_large", LOG_FULL);
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
	if (init_malloc() == EXIT_FAILURE)
		return (NULL);
	malloc_log(LOG_FULL, "Malloc_log_test - %d and some more\n", size);
	if (size <= MALLOC_SMALL)
		return (malloc_small(size));
	return (malloc_large(size));
}
