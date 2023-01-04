/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:39:02 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 21:47:06 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	src_len;

	src_len = ft_strlen(src);
	dst = (char *)malloc((src_len + 1) * sizeof(char));
	if (dst == 0)
		return (0);
	dst[src_len] = 0;
	ft_strlcpy(dst, src, src_len + 1);
	return (dst);
}
