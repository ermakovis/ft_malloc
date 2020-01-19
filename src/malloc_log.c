#include "malloc.h"

int			malloc_log_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		malloc_log(char *message, int loglevel)
{
	if (loglevel != g_malloc->loglevel)
		return ;
	write(1, message, malloc_log_strlen(message));	
	write(1, "\n", 1);
	return ;
}
