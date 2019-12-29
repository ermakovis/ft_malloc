#include "libft.h"
#include "ft_malloc.h"

static void	find_block_split(t_block *block, size_t size)
{
	t_block	*next;
	size_t	block_size;


	block_size = sizeof(t_block);
	if (block->size - size <= block_size)	
		return ;
	next = (void*)block + block_size + size;
	next->next = block->next;
	next->size = block->size - size - block_size;
	next->free = 1;
	block->size = size;
	block->next = next;
}

int	 find_block(t_block **block, t_block *ablock, size_t size)
{
	t_block	*curr;

	curr = ablock;
	while (curr)
	{
		if (curr->free == 1 && curr->size >= size)
		{
			find_block_split(curr, size);
			curr->free = 0;
			*block = curr;
			return (EXIT_SUCCESS);
		}
		curr = curr->next;
	}
	return (EXIT_FAILURE);
}

void	*malloc_mmap(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

int		init_malloc_block(t_block **ablock, t_block *block, size_t size)
{
	*ablock = block;
	block->free = 1;
	block->next = 0;
	block->size = size - sizeof(t_block);
}

int		init_malloc(void)
{
	size_t	page_size;
	size_t	tiny_size;
	size_t	small_size;
	size_t	total_size;

	if (g_malloc)
		return (EXIT_SUCCESS);
	page_size = getpagesize();
	tiny_size = 100 * (MALLOC_TINY * page_size + sizeof(t_list));
	small_size = 100 * (MALLOC_SMALL * page_size + sizeof(t_list));
	total_size = sizeof(t_malloc) + tiny_size + small_size;
	if (!(g_malloc = malloc_mmap(sizeof(t_malloc) + tiny_size + small_size)))
		return (EXIT_FAILURE);
	bzero(g_malloc, total_size);
	init_malloc_block(&g_malloc->tiny, (t_block*)(g_malloc + 1), tiny_size);
	init_malloc_block(&g_malloc->small, (void*)g_malloc->tiny + tiny_size, \
		small_size);
	return (EXIT_SUCCESS);
}
