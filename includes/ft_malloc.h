#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <unistd.h>
# include <assert.h>
# define MALLOC_TINY 64
# define MALLOC_SMALL 512
# define MALLOC_TINY_ZONE 4098 * 100 * MALLOC_TINY 
# define MALLOC_SMALL_ZONE 4098 * 100 * MALLOC_SMALL

typedef struct		s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
	struct s_block	*prev;
}					t_block;

typedef struct		s_zone
{
	t_block			*block;
	void			*start;
	void			*end;
	size_t			max_block;
	struct s_zone	*next;
}					t_zone;


typedef struct		s_malloc
{
	t_zone			*tiny;
	t_zone			*small;
	t_block			*large;
}					t_malloc;

t_malloc			*g_malloc;

void				*malloc(size_t size);
void				free(void *ptr);
void				print_sizet(size_t num);

//void				show_alloc_mem(void);
int					init_malloc(void);
void				*malloc_mmap(size_t size);
int 				find_block(t_block **block, t_zone *zone, size_t size);
int					find_zone(t_zone **zone, size_t size);
#endif
