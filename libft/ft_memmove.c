/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:32:54 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 21:52:13 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst <= src)
	{
		ft_memcpy(dst, src, len);
	}
	else
	{
		while (len != 0)
		{
			len--;
			ft_memcpy((dst + len), (src + len), 1);
		}
	}
	return (dst);
}	
