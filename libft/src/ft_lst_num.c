/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:09:44 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 15:41:05 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_num(t_list *alist, size_t num)
{
	size_t	i;

	i = 0;
	while (alist)
	{
		if (i++ == num)
			return (alist);
		alist = alist->next;
	}
	return (NULL);
}
