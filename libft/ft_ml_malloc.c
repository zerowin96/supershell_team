/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ml_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:51:28 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/10 09:20:42 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ml_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == 0)
	{
		write(2, "\n", 1);
		write(2, "Memory Allocation Error\n", 25);
		exit(1);
	}
	return (ret);
}
