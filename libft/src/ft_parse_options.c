#include "libft.h"

static int		add_flag(char *line, char *str, int *flags)
{
	int		shift;
	int		i;

	shift = 0;
	i = 0;
	while (str[++i])
	{
		if ((shift = ft_strchrlen(line, str[i])) == -1)
			return (0);
		*flags |= (1 << shift);
	}
	return (1);
}

int				ft_parse_options(char *line, char **options, int *flags)
{
	int		count;

	count = 0;
	*flags = 0;
	while (options[count] && options[count][0] == '-' && options[count][1])
	{
		if (!(add_flag(line, options[count], flags)))
			return (-1);
		count++;
	}
	return (count);
}
