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

	while (i++ < 1000)
	{
		ptr = malloc(500);
		printf("%d - %p\n", i, ptr);
	}

	return (1);
}
