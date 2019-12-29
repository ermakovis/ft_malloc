#include "libft.h"
#include "ft_malloc.h"

static int	print_line(char *line)
{
	char 	*str;
	int		len;

	len = ft_strlen(line) + 1;
	str = (char*)malloc(len);
	ft_strcpy(str, line);
	ft_printf("%s", str);
	free(str);
}

int main(void)
{
	print_line("HELLO\n");
	print_line("WORLD\n");
	print_line("and leaks\n");
	malloc(50);
	malloc(150);
	malloc(5000);
	show_alloc_mem();
	return (1);
}
