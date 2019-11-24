/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_item_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:12:47 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 16:06:18 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_item_type(char *path)
{
	t_stat	stat_struct;

	if (!path || !*path)
		return (-1);
	if (stat(path, &stat_struct) == -1)
		return (0);
	if (S_ISSOCK(stat_struct.st_mode))
		return (1);
	if (S_ISDIR(stat_struct.st_mode))
		return (2);
	if (S_ISLNK(stat_struct.st_mode))
		return (3);
	if (S_ISFIFO(stat_struct.st_mode))
		return (4);
	if (S_ISCHR(stat_struct.st_mode))
		return (5);
	if (S_ISBLK(stat_struct.st_mode))
		return (6);
	return (-1);
}
