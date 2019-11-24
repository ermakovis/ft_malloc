#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <unistd.h>
# include <assert.h>
# define MALLOC_TINY 64
# define MALLOC_SMALL 512

typedef struct		s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
}					t_block;

typedef struct		s_malloc
{
	t_block			*tiny;
	void			*tiny_start;
	void			*tiny_end;
	t_block			*small;
	void			*small_start;
	void			*small_end;
	t_block			*large;
	void			*large_start;

}					t_malloc;

t_malloc			*g_malloc;

void				*malloc(size_t size);
void				free(void *ptr);

void				show_alloc_mem(void);
int					init_malloc(void);
void				*malloc_mmap(size_t size);
int 				find_block(t_block **block, t_block *ablock,\
					size_t size);
#endif
