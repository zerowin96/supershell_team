/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:57:42 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/20 13:42:27 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ndl_len;

	ndl_len = ft_strlen(needle);
	if (*needle == 0)
		return ((char *)haystack);
	while ((*haystack != 0) && (len >= ndl_len))
	{
		if (ft_strncmp(haystack, needle, ndl_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
