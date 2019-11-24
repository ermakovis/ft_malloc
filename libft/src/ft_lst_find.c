/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:07:42 by tcase             #+#    #+#             */
/*   Updated: 2019/09/28 20:05:43 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_find(t_list *alist, void *data_ref, int (*cmp)())
{
	while (alist)
	{
		if ((*cmp)(alist->content, data_ref) == 0)
			return (alist);
		alist = alist->next;
	}
	return (NULL);
}
