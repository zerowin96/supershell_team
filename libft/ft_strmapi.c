/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:25:44 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/20 13:42:06 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret_str;
	char	*ret_str_temp;
	int		index;

	ret_str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ret_str == 0)
		return (ret_str);
	ft_bzero(ret_str, (ft_strlen(s) + 1));
	ret_str_temp = ret_str;
	index = 0;
	while (*s != 0)
		*(ret_str++) = f(index++, *(s++));
	return (ret_str_temp);
}
