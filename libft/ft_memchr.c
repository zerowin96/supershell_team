/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:37:44 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 21:43:42 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*res;

	res = (unsigned char *)s;
	while (n != 0)
	{
		if (*res == (unsigned char)c)
			return ((void *)res);
		res++;
		n--;
	}
	return (0);
}
