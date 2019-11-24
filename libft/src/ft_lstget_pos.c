#include "libft.h"

size_t		ft_lstget_pos(t_list *alist, void *data_ref, int (*cmp)())
{
	size_t	ret;

	ret = 0;
	while(alist)
	{
		if ((*cmp)(alist->content, data_ref) == 0)
			return (ret);
		ret++;
		alist = alist->next;
	}
	return (0);
}
