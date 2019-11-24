/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 20:11:43 by tcase             #+#    #+#             */
/*   Updated: 2019/08/24 16:02:25 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_test_path(char *path)
{
	t_stat	stat;
	int		ret;

	ret = 0;
	if (!path || !*path)
		return (-1);
	if (lstat(path, &stat) == -1)
		return (0);
	if (S_IRUSR & stat.st_mode)
		ret += 4;
	if (S_IWUSR & stat.st_mode)
		ret += 2;
	if (S_IXUSR & stat.st_mode)
		ret += 1;
	return (ret);
}
