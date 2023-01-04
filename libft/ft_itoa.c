/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:23:17 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/19 21:42:38 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	num_print(int n)
{
	if (n < 0)
		return ((char)(-n + '0'));
	return ((char)(n + '0'));
}

static int	decimal_len(int n)
{
	int	digits;

	digits = 1;
	while (n / 10)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*ret_str;
	int		ret_str_len;
	char	sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	ret_str_len = decimal_len(n) + sign + 1;
	ret_str = (char *)malloc((ret_str_len) * sizeof(char));
	if (ret_str == 0)
		return (ret_str);
	ft_bzero(ret_str, ret_str_len);
	if (n == 0)
		ret_str[0] = '0';
	while (n != 0)
	{
		ret_str[(ret_str_len--) - 2] = num_print(n % 10);
		n = n / 10;
	}
	if (sign == 1)
		ret_str[0] = '-';
	return (ret_str);
}
