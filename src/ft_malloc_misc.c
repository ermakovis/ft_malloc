#include "ft_malloc.h"

void	print_sizet(size_t num)
{
	char	ch;

	if (num >= 10)
		print_sizet(num / 10);
	ch = ((num % 10) + '0');
	write(1, &ch, 1);
}

void	*malloc_mmap(size_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	//ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

int		init_malloc(void)
{
	if (g_malloc)
		return (EXIT_SUCCESS);
	if (!(g_malloc = malloc_mmap(sizeof(t_malloc))))
		return (EXIT_FAILURE);
	bzero(g_malloc, sizeof(t_malloc));
	return (EXIT_SUCCESS);
}
