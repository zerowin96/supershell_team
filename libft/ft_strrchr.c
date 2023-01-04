/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:49:57 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 20:57:35 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*e;
	char	t;

	t = (char) c;
	e = 0;
	while (*s != 0)
	{
		if (*s == t)
			e = (char *)s;
		s++;
	}
	if (t == 0)
		return ((char *)s);
	return (e);
}
