#include "libft.h"
#include "ft_malloc.h"

void	show_alloc_mem_printlist(t_block *block)
{
	while (block)
	{
		ft_printf("%p - %p : %3d bytes : %d\n",\
			block + 1, (void*)(block + 1) + block->size, block->size,\
			block->free);
		block = block->next;
	}
}

void	show_alloc_mem(void)
{
	t_list		*list;

	if (!g_malloc)
	{
		ft_dprintf(2, "show_alloc_mem: malloc unintialised\n");
		return ;
	}
	ft_printf("TINY  : %p\n", g_malloc->tiny_start);
	show_alloc_mem_printlist(g_malloc->tiny);
	ft_printf("SMALL : %p\n", g_malloc->small_start);
	show_alloc_mem_printlist(g_malloc->small);
	ft_printf("LARGE : %p\n", g_malloc->large_start);
	show_alloc_mem_printlist(g_malloc->large);
}
