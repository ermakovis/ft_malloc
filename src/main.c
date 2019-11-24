#include "libft.h"
#include "ft_malloc.h"

static int	print_line(char *line)
{
	char 	*str;
	int		len;

	len = ft_strlen(line) + 1;
	str = (char*)malloc(len);
	ft_printf("%p\n", str);
	ft_strcpy(str, line);
	ft_printf("%s\n", str);
	free(str);
}

int main(void)
{
	print_line("HELLO");
	print_line("WORLD");
	print_line("and leaks");
	show_alloc_mem();
	return (1);
}
