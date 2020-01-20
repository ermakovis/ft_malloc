#include "malloc.h"

static void free_merge_next(t_block *block)
{
	if (!block->next || block->next->free == 0)
		return ;
	malloc_log(LOG_FULL, "Merging with next block");
	malloc_log(LOG_FULL, "\tOld block size - %d next block size - %d", 
		block->size, block->next->size);
	block->size += block->next->size + sizeof(t_block);
	block->next = block->next->next;
	malloc_log(LOG_FULL, "\tOld block size - %d", block->size);
}

static void	free_merge_prev(t_block *block)
{
	if (!block->prev || block->prev->free == 0)
		return ;
	malloc_log(LOG_FULL, "Merging with previous block");
	block->prev->next = block->next;
	malloc_log(LOG_FULL, "\tOld prev block size - %d, prev block size - %d",
		block->size, block->prev->size);
	block->prev->size += block->size + sizeof(t_block);
	malloc_log(LOG_FULL, "\tNew prev block size - %d", block->prev->size);
}

void	free_large(t_block *block)
{
	errno = 0;
	malloc_log(LOG_BRIEF, "Munmap - call");
	if (munmap((void*)block, block->size + sizeof(t_block)) == -1)
	{
		malloc_log(LOG_BRIEF, "%sERROR - Mmap retured ZERO%s",\
			COL_RED, COL_RESET);
	}
	malloc_log(LOG_FULL, "errno - %d", errno);
	malloc_log(LOG_BRIEF, "Munmap successfull");
}

void	free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_malloc->mutex);
	block = (t_block*)ptr - 1;
	malloc_log(LOG_BRIEF, "Free for a block of size %d called", block->size);
	if (block->size > MALLOC_SMALL)
	{
		pthread_mutex_unlock(&g_malloc->mutex);
		return (free_large(block));
	}
	block->free = 1;
	free_merge_next(block);
	free_merge_prev(block);
	pthread_mutex_unlock(&g_malloc->mutex);
}

