/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:57:28 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/20 13:57:52 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	nbr_printer(int n, int fd)
{
	unsigned char	c;

	if (n != 0)
	{
		nbr_printer(n / 10, fd);
		n = n % 10;
		if (n < 0)
			n = -n;
		c = (unsigned char)(n) + '0';
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	if (n == 0)
		write(fd, "0", 1);
	else
		nbr_printer(n, fd);
}
