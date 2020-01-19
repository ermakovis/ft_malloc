#include "malloc.h"

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
	if (ptr == MAP_FAILED)
	{
		malloc_log(LOG_BRIEF, "%sERROR - Mmap retured ZERO%s",\
			COL_RED, COL_RESET);
		return (NULL);
	}
	return (ptr);
}

int		init_malloc(void)
{
	char *loglevel;

	if (g_malloc)
		return (EXIT_SUCCESS);
	if (!(g_malloc = malloc_mmap(sizeof(t_malloc))))
		return (EXIT_FAILURE);
	bzero(g_malloc, sizeof(t_malloc));
	if (!(loglevel = getenv("MALLOC_LOG")))
		g_malloc->loglevel = LOG_NONE;
	if (loglevel && !ft_strcmp(loglevel, "brief"))
		g_malloc->loglevel = LOG_BRIEF;
	if (loglevel && !ft_strcmp(loglevel, "full"))
		g_malloc->loglevel = LOG_FULL;
	if (loglevel && !ft_strcmp(loglevel, "file"))
		g_malloc->loglevel = LOG_FILE;
	malloc_log(LOG_FULL, "Loglevel - %d", g_malloc->loglevel);
	return (EXIT_SUCCESS);
}
