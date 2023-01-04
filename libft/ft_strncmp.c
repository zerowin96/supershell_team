/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:36:30 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 13:19:56 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	result;

	if (n == 0)
		return (0);
	if (n > 0)
		n--;
	while ((n != 0) && (*s1 != 0))
	{
		result = *(unsigned char *)s1 - *(unsigned char *)s2;
		if (result != 0)
			return (result);
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
