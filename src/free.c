#include "libft.h"
#include "ft_malloc.h"

static void free_merge(t_block *block)
{
	if (!block->next || block->next->free == 0)
		return ;
	block->size += block->next->size + sizeof(t_block);
	block->next = block->next->next;
}

void	free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	block = (t_block*)ptr - 1;
	block->free = 1;
	free_merge(block);
}

