/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:06:16 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/20 13:58:08 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	new_str_counter(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
			if ((*(s + 1) == c) || !(*(s + 1)))
				count++;
		s++;
	}
	return (count);
}

static char	*new_str_gen(char const *s, char c)
{
	char	*ret;
	size_t	str_len;

	str_len = 0;
	while ((s[str_len] != c) && s[str_len])
		str_len ++;
	ret = (char *)malloc((str_len + 1) * sizeof(char));
	if (ret == 0)
		return (ret);
	ft_bzero(ret, str_len + 1);
	ft_memcpy(ret, s, str_len);
	return (ret);
}

static int	putin(char **ret, char const *s, char c)
{
	while (*s)
	{
		while (*s == c && *s != 0)
			s++;
		if (*s != c && *s != 0)
		{
			*ret = new_str_gen(s, c);
			if (*ret == 0)
				return (0);
			ret++;
		}
		while (*s != c && *s != 0)
			s++;
	}
	*ret = NULL;
	return (1);
}

static void	*clean(char **ret)
{
	size_t	index;

	index = 0;
	while (ret[index])
	{
		free(ret[index]);
		index++;
	}
	free(ret[index]);
	free(ret);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	char	**ret_temp;
	size_t	ret_len;

	ret_len = new_str_counter(s, c);
	ret = (char **)malloc((ret_len + 1) * sizeof(char *));
	if (ret == 0)
		return (ret);
	ft_bzero(ret, ret_len + 1);
	if (putin(ret, s, c) == 0)
		return ((char **)clean(ret));
	ret_temp = ret;
	return (ret_temp);
}
