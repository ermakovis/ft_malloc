#include "ft_malloc.h"

static void *malloc_small(size_t size)
{
	t_block	*ret;
	t_zone	*zone;

	size = (size + 15) & ~15;
	if (find_zone(&zone, size) == EXIT_FAILURE)
	{
		write(1, "!", 1);
		return (NULL);
	}
	if (find_block(&ret, zone, size) == EXIT_SUCCESS)
		return (ret + 1);
	write(1, "e", 1);
	return (NULL);
}

static void *malloc_large(size_t size)
{
	t_block	*ret;

	//write(1, "l\n", 2);
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
	//print_sizet(size);
	//write(1, "\n", 1);
	if (init_malloc() == EXIT_FAILURE)
		return (NULL);
	if (size <= MALLOC_SMALL)
		return (malloc_small(size));
	return (malloc_large(size));
}
