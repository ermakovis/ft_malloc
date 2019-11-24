/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 15:29:39 by tcase             #+#    #+#             */
/*   Updated: 2019/07/28 15:29:43 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstpop(t_list **alst, void (*del)(void*, size_t))
{
	t_list *tmp;

	if (!alst || !*alst)
		return ;
	tmp = (*alst)->next;
	del((*alst)->content, ((*alst)->content_size));
	free(*alst);
	*alst = tmp;
}
