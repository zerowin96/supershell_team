/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:18:02 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 21:46:57 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if ((start >= ft_strlen(s)) || *s == 0)
		len = 0;
	else if (len >= ft_strlen(s + start))
		len = ft_strlen(s + start);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret == 0)
		return (0);
	ft_bzero(ret, len + 1);
	ft_memcpy(ret, s + start, len);
	return (ret);
}
