/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:17:14 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/18 20:55:48 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (src[count] != 0)
		count++;
	if (dstsize == 0)
		return (count);
	while ((src[index] != 0) && (1 < dstsize))
	{
		dst[index] = src[index];
		index++;
		dstsize--;
	}
	dst[index] = 0;
	return (count);
}
