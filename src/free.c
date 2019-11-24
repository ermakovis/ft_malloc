#include "libft.h"
#include "ft_malloc.h"

void	free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	ft_putstr("My free\n");
	block = (t_block*)ptr - 1;
	assert(block->free == 0);
	block->free = 1;
}

