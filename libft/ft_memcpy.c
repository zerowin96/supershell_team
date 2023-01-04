/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:26:01 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 15:24:32 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	if ((dst == 0) && (src == 0))
		return (0);
	index = 0;
	while (index < n)
	{
		*(((unsigned char *)dst) + index) = *(((unsigned char *)src) + index);
		index++;
	}
	return (dst);
}
