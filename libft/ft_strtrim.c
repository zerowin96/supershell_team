/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:12:04 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 14:34:22 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*first_char_finder(const char *s, const char *str)
{
	if (*s == 0)
		return ((char *)s);
	while ((*s != 0) && (ft_strchr(str, *s) != 0))
		s++;
	return ((char *)s);
}

static size_t	get_last_char_idx(const char *s, const char *str)
{
	size_t	str_len;

	str_len = ft_strlen(s);
	if (str_len == 0)
		return (0);
	while ((ft_strchr(str, s[str_len - 1]) != 0) && (s[str_len - 1] != 0))
		str_len--;
	return (str_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	char	*first_char;
	size_t	index;

	first_char = first_char_finder(s1, set);
	index = get_last_char_idx(first_char, set);
	ret = (char *)malloc((index + 1) * sizeof(char));
	if (ret == 0)
		return (ret);
	ft_bzero(ret, index + 1);
	ft_memcpy(ret, first_char, index);
	return (ret);
}
