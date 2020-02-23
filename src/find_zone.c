#include "malloc.h"

static void	find_zone_add(t_zone **azone, t_zone *zone)
{
	zone->next = *azone;
	*azone = zone;
}

static int	find_zone_create(t_zone **zone, size_t size)
{
	t_zone *ret;
	size_t block_shift;

	if ((ret = malloc_mmap(size)) == MAP_FAILED)
		return (EXIT_FAILURE);
	block_shift = (sizeof(t_zone) + MALLOC_ALIGN) & ~MALLOC_ALIGN;
	bzero(ret, size);
	ret->block = (void*)ret + block_shift;
	ret->block->free = 1;
	ret->block->next = 0;
	ret->block->prev = 0;
	ret->block->size = size - block_shift;
	ret->max_block = 0;
	ret->next = 0;
	*zone = ret;
	return (EXIT_SUCCESS);
}

static int	find_zone_small(t_zone **zone, size_t size)
{
	t_zone *azone;
	t_zone *new_zone;

	malloc_log(LOG_BRIEF, "Looking for a zone");
	azone = g_malloc->small;
	while (azone)
	{
		malloc_log(LOG_FULL, "\tNext zone");
		if (azone->max_block >= size + sizeof(t_block))
		{
			*zone = azone;
			return (EXIT_SUCCESS);
		}
		azone = azone->next;
	}
	malloc_log(LOG_BRIEF, "Creating new zone of size %d", MALLOC_SMALL_ZONE);
	if (find_zone_create(&new_zone, MALLOC_SMALL_ZONE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*zone = new_zone;
	find_zone_add(&g_malloc->small, new_zone);
	return (EXIT_SUCCESS);
}

static int	find_zone_tiny(t_zone **zone, size_t size)
{
	t_zone *azone;
	t_zone *new_zone;

	malloc_log(LOG_BRIEF, "Looking for a zone");
	azone = g_malloc->tiny;
	while (azone)
	{
		//malloc_log(LOG_FULL, "\tNext zone");
		if (azone->max_block >= size + sizeof(t_block))
		{
			*zone = azone;
			return (EXIT_SUCCESS);
		}
		azone = azone->next;
	}
	malloc_log(LOG_BRIEF, "Creating new zone of size %d", MALLOC_TINY_ZONE);
	if (find_zone_create(&new_zone, MALLOC_TINY_ZONE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	find_zone_add(&g_malloc->tiny, new_zone);
	*zone = new_zone;
	malloc_log(LOG_BRIEF, "Zone creation successfull");
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
