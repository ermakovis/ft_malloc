#include "malloc.h"

static void *malloc_small(size_t size)
{
	t_block	*ret;
	t_zone	*zone;

	malloc_log(LOG_BRIEF, "Size of malloc is - SMALL");
	if (find_zone(&zone, size) == EXIT_FAILURE)
	{
		malloc_log(LOG_BRIEF, "%sERROR - Failed to find zone%s",\
			COL_RED, COL_RESET);
		return (NULL);
	}
	if (find_block(&ret, zone, size) == EXIT_SUCCESS)
		return (ret + 1);
	malloc_log(LOG_BRIEF, "%sERROR - Failed to find block%s",\
		COL_RED, COL_RESET);
	return (NULL);
}

static void *malloc_large(size_t size)
{
	t_block	*ret;

	malloc_log(LOG_BRIEF, "Size of malloc is - LARGE");
	errno = 0;
	if (!(ret = malloc_mmap(size + sizeof(t_block))))
	{
		malloc_log(LOG_BRIEF, "%sERROR - Mmap retured ZERO%s",\
			COL_RED, COL_RESET);
		return (NULL);
	}
	malloc_log(LOG_FULL, "errno - %d", errno);
	malloc_log(LOG_FULL, "ptr recived - %d", ret);
	malloc_log(LOG_FULL, "Mmap successfull");
	ret->size = size;
	ret->free = 0;
	ret->prev = 0;
	ret->next = g_malloc->large;
	//if (g_malloc->large)
	//	g_malloc->large->prev = ret;
	g_malloc->large = ret;
	malloc_log(LOG_FULL, "Malloc successfull");
	return (ret + 1);
}

void	*malloc(size_t size)
{
	void *ret;

	if (init_malloc() == EXIT_FAILURE)
		return (NULL);
	pthread_mutex_lock(&g_malloc->mutex);
	malloc_log(LOG_FULL, "pagesize %d", getpagesize());
	size = (size + MALLOC_ALIGN) & ~MALLOC_ALIGN;
	malloc_log(LOG_BRIEF, "Malloc started - %d", size);
	if (size <= MALLOC_SMALL)
		ret = malloc_small(size);
	else
		ret = malloc_large(size);
	pthread_mutex_unlock(&g_malloc->mutex);
	return (ret);
}
