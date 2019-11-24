#include "libft.h"

void		ft_lst_remove(t_list **alist, t_list *ref, void (*del)())
{
	t_list	*prev;
	t_list	*curr;

	prev = 0;
	curr = *alist;
	while (curr)
	{
		if (curr == ref)
		{
			if (!prev)
				*alist = curr->next;
			else
				prev->next = curr->next;
			del(curr->content, curr->content_size);
			ft_memdel((void**)&curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
