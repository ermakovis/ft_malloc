#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>

static void *malloc_small(size_t size, t_block *block)
{
	t_block	*ret;

	if (find_block(&ret, block, size) == EXIT_SUCCESS)
		return (ret + 1);
	return (NULL);
}

static void *malloc_large(size_t size, t_block *block)
{
	t_block	*ret;

	if (find_block(&ret, block, size) == EXIT_SUCCESS)
		return (ret + 1);
	if (!(ret = malloc_mmap(size + sizeof(t_block))))
		return (NULL);
	ret->free = 0;
	ret->size = size;
	ret->next = g_malloc->large;
	g_malloc->large = ret;
	return (ret + 1);
}

void	*malloc(size_t size)
{
	init_malloc();
	if (size <= MALLOC_TINY)
		return (malloc_small(size, g_malloc->tiny));
	if (size <= MALLOC_SMALL)
		return (malloc_small(size, g_malloc->small));
	return (malloc_large(size, g_malloc->large));
}
