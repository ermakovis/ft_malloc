#include "malloc.h"

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
	ret->max_block = 0;
	ret->next = 0;
	*zone = ret;
	return (EXIT_SUCCESS);
}

static int	find_zone_small(t_zone **zone, size_t size)
{
	t_zone *azone;
	t_zone *last;
	t_zone *new_zone;

	last = 0;
	azone = g_malloc->small;
	while (azone)
	{
		//malloc_log("Checking zone", LOG_FULL);
		if (azone->max_block >= size + sizeof(t_block))
		{
			*zone = azone;
			return (EXIT_SUCCESS);
		}
		last = azone;
		azone = azone->next;
	}
	if (find_zone_create(&new_zone, MALLOC_SMALL_ZONE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!last)
		g_malloc->small = new_zone;
	else
		last->next = new_zone;
	*zone = new_zone;
	return (EXIT_SUCCESS);
}

static int	find_zone_tiny(t_zone **zone, size_t size)
{
	t_zone *azone;
	t_zone *last;
	t_zone *new_zone;

	last = 0;
	azone = g_malloc->tiny;
	while (azone)
	{
		//malloc_log("Checking zone", LOG_FULL);
		if (azone->max_block >= size + sizeof(t_block))
		{
			*zone = azone;
			return (EXIT_SUCCESS);
		}
		last = azone;
		azone = azone->next;
	}
	if (find_zone_create(&new_zone, MALLOC_SMALL_ZONE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!last)
		g_malloc->tiny = new_zone;
	else
	{
		write(1, "X\n", 2); 
		last->next = new_zone;
	}
	*zone = new_zone;
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
