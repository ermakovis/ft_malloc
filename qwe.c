#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int		main(void)
{
	char *str;
	void	*ptr;
	int		i;

	i = 0;

	while (i++ < 100)
	{
		ptr = malloc(rand() % 64);
		//printf("%d - %p\n", i, ptr);
		free(ptr);
	}
	while (i++ < 100)
	{
		ptr = malloc(rand() % 512);
		//printf("%d - %p\n", i, ptr);
		free(ptr);
	}
	while (i++ < 100)
	{
		ptr = malloc(rand() % 5024);
		//printf("%d - %p\n", i, ptr);
		free(ptr);
	}
	return (1);
}
