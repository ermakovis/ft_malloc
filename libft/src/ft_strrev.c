#include "libft.h"

char	*ft_strrev(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(line) - 1;
	while (i < j)
	{
		ft_swap(&line[i], &line[j]); 
		i++;
		j--;
	}
	return (line);
}
