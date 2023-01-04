/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:47:20 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/20 14:35:34 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

static int	sign_detector(const char *str)
{
	int	sign;

	sign = 0;
	if (*str == '-')
	{
		sign = -1;
	}
	else if (*str == '+')
	{
		sign = +1;
	}
	return (sign);
}

static int	white_space(const char *str)
{
	if (*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		return (1);
	else
		return (0);
}

static long long	over_detect(long long val, char c, int sign)
{
	long long	ll_d10;

	ll_d10 = 922337203685477580;
	if (val > ll_d10)
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	else if (val == ll_d10 && (c - '0') >= 8)
	{
		if (c - '0' == 9)
		{	
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		else if (sign == 1)
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	value;
	int			sign;

	sign = 1;
	value = 0;
	while (white_space(str) != 0)
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = sign_detector(str);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (over_detect(value, *str, sign) != 1)
			return (over_detect(value, *str, sign));
		value = value * 10 + (*str - '0');
		str++;
	}
	return (sign * value);
}
