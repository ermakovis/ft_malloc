#include "ft_malloc.h"

static int	find_zone_create(t_zone **zone, size_t size)
{
	t_zone *ret;

	if (!(ret = malloc_mmap(size)))
		return (EXIT_FAILURE);
	bzero(ret, size);
	ret->block = (void*)(ret + sizeof(t_zone));
	ret->block->free = 1;
	ret->block->next = 0;
	ret->block->prev = 0;
	ret->block->size = size - sizeof(t_zone);
	ret->start = ret + 1;
	ret->end = (void*)ret + size;
	ret->max_block = 0;
	ret->next = 0;
	*zone = ret;
	return (EXIT_SUCCESS);
}

static int	find_zone_small(t_zone **zone, size_t size)
{
	t_zone *azone;
	t_zone *last;

	last = 0;
	azone = g_malloc->small;
	while (azone)
	{
		if (azone->max_block >= size + sizeof(t_block))
		{
			*zone = azone;
			return (EXIT_SUCCESS);
		}
		last = azone;
		azone = azone->next;
	}
	if (find_zone_create(&last, MALLOC_SMALL_ZONE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!g_malloc->small)
		g_malloc->small = last;
	*zone = last;
	return (EXIT_SUCCESS);
}

static int	find_zone_tiny(t_zone **zone, size_t size)
{
	t_zone *azone;
	t_zone *last;

	last = 0;
	azone = g_malloc->tiny;
	while (azone)
	{
		if (azone->max_block >= size + sizeof(t_block))
		{
			*zone = azone;
			return (EXIT_SUCCESS);
		}
		last = azone;
		azone = azone->next;
	}
	if (find_zone_create(&last, MALLOC_TINY_ZONE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!g_malloc->tiny)
		g_malloc->tiny = last;
	*zone = last;
	return (EXIT_SUCCESS);
}

int		find_zone(t_zone **zone, size_t size)
{
	if (size <= MALLOC_TINY)
		return (find_zone_tiny(zone, size)); 
	if (size <= MALLOC_SMALL)
		return (find_zone_small(zone, size));
	return (EXIT_FAILURE);
}
