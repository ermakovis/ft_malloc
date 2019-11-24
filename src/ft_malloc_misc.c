#include "libft.h"
#include "ft_malloc.h"

int	 find_block(t_block **block, t_block *ablock, size_t size)
{
	t_block	*curr;

	curr = ablock;
	while (curr)
	{
		if (curr->free == 1 && curr->size >= size)
		{
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
	g_malloc->tiny_start= g_malloc + 1;
	g_malloc->tiny_end = g_malloc->tiny_start + tiny_size;	
	g_malloc->small_start = g_malloc->tiny_end + 1;
	g_malloc->small_end = g_malloc->small_start + small_size;
	g_malloc->large_start = g_malloc->small_end + 1;
	return (EXIT_SUCCESS);
}
