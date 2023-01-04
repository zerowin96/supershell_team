/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:44:44 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 20:59:18 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (((*s != (char)c)) && (*s != 0))
		s++;
	if ((char)c == 0)
		return ((char *)s);
	else if (*s == 0)
		return (0);
	else
		return ((char *)s);
}
