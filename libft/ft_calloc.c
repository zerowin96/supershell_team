/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 09:48:53 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/10 09:17:20 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*address;

	address = (void *)ml_malloc(count * size);
	if (address == 0)
		exit (1);
	ft_bzero(address, count * size);
	return (address);
}
