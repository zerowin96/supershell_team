/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:43:50 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 21:43:29 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				result;
	unsigned char	*sa;
	unsigned char	*sb;

	sa = (unsigned char *)s1;
	sb = (unsigned char *)s2;
	while (n != 0)
	{
		result = *sa - *sb;
		if (result != 0)
			return (result);
		sa = sa + 1;
		sb = sb + 1;
		n--;
	}
	return (0);
}
