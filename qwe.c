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

	while (i++ < 200000)
	{
		ptr = malloc(rand() % 5000);
		printf("%d - %p\n", i, ptr);
	}

	return (1);
}
