#include "libft.h"

void	ft_lstrev(t_list **alist)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	prev = 0;
	next = 0;
	curr = *alist;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*alist = prev;
}

