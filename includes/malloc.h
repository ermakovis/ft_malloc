#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
//For malloc_log
# include <stdarg.h>
//Atm only for EXIT_FAILURE/EXIT_SUCCESS macros
# include <stdlib.h>
# include <errno.h>

# define MALLOC_TINY 		64
# define MALLOC_SMALL 		512
# define MALLOC_TINY_ZONE 	4098 * 10
# define MALLOC_SMALL_ZONE 	4098 * 20
# define LOG_NONE			0
# define LOG_FILE 			1
# define LOG_BRIEF 			(1 << 2)
# define LOG_FULL 			(1 << 1)
# define COL_RED			"\x1b[31m"
# define COL_YELLOW			"\x1b[33m"
# define COL_RESET			"\x1b[0m"

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
	int				loglevel;
}					t_malloc;

t_malloc			*g_malloc;

void				*malloc(size_t size);
void				free(void *ptr);
void				print_sizet(size_t num);

//void				show_alloc_mem(void);
int					init_malloc(void);
void				*malloc_mmap(size_t size);
void				malloc_log(int loglevel, const char *format, ...);
int 				find_block(t_block **block, t_zone *zone, size_t size);
int					find_zone(t_zone **zone, size_t size);

/*
			UTILS
*/
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strlen(const char *str);
int					ft_strchrlen(const char *str, int c);
void				ft_putstr(const char *str);
void				bzero(void *ptr, size_t size);

#endif
