#include "ft_malloc.h"

static void set_zone_max_size(t_zone *zone)
{
	t_block	*block;

	block = zone->block;
	zone->max_block = 0;
	while (block)
	{
		if (block->free == 1 && zone->max_block < block->size)
			zone->max_block = block->size;
		block = block->next;
	}
}

static void	find_block_split(t_block *left, size_t size)
{
	t_block	*right;
	size_t	block_size;

	block_size = sizeof(t_block);
	right = (void*)left + block_size + size;
	right->next = left->next;
	right->prev = left;
	right->size = left->size - size - block_size;
	right->free = 1;
	left->size = size;
	left->next = right;
}

int	 find_block(t_block **block, t_zone *zone, size_t size)
{
	t_block	*curr;

	curr = zone->block;;
	while (curr)
	{
		if (curr->free == 1 && curr->size >= size + sizeof(t_block))
		{
			find_block_split(curr, size);
			set_zone_max_size(zone);
			curr->free = 0;
			*block = curr;
			return (EXIT_SUCCESS);
		}
		curr = curr->next;
	}
	return (EXIT_FAILURE);
}
