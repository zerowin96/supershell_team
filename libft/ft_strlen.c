/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:00:02 by minsulee          #+#    #+#             */
/*   Updated: 2023/01/07 15:48:44 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	count;

	//modified
	if (!s)
		return (0);
	//part done

	count = 0;
	while (*s != 0)
	{
		count++;
		s++;
	}
	return (count);
}
