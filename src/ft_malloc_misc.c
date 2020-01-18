#include "libft.h"
#include "ft_malloc.h"

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

int	 find_block(t_block **block, t_block *ablock, size_t size)
{
	t_block	*curr;

	curr = ablock;
	while (curr)
	{
		if (curr->free == 1 && curr->size >= size + sizeof(t_block))
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

static t_block		*init_malloc_block(t_block *block, size_t size)
{
	block->free = 1;
	block->next = 0;
	block->prev = 0;
	block->size = size - sizeof(t_block);
	return (block);
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
	g_malloc->tiny = init_malloc_block((t_block*)(g_malloc + 1), tiny_size);
	g_malloc->small = init_malloc_block((void*)g_malloc->tiny + tiny_size, \
		small_size);
	return (EXIT_SUCCESS);
}
