/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:45:50 by yeham             #+#    #+#             */
/*   Updated: 2023/02/08 19:10:18 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	num_error(unsigned long long int num, int buho, int c)
{
	if (num > 922337203685477580)
	{
		ft_putstr_fd("numeric argument required\n", 2);
		exit(2);
	}
	if (buho == -1 && num == 922337203685477580 && c > 8)
	{
		ft_putstr_fd("numeric argument required\n", 2);
		exit(2);
	}
	if (buho == 1 && num == 922337203685477580 && c > 7)
	{
		ft_putstr_fd("numeric argument required\n", 2);
		exit(2);
	}
}

int	ft_atoi2(const char *str)
{
	int						buho;
	int						i;
	unsigned long long int	num;

	num = 0;
	buho = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
	{	
		buho *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num_error(num, buho, (str[i] - '0'));
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * buho);
}

void	many_argument_error(char *next_command)
{
	if (next_command != 0)
	{
		ft_putstr_fd("too many arguments\n", 2);
		exit (1);
	}
}

void	ft_exit(char *command, char *next_command)
{
	int	i;
	int	value;

	i = 0;
	write(1, "exit\n", 5);
	if (command[0] == '-' && command[1] == '-' && command[2] == '\0' \
		&& next_command == 0)
		exit(0);
	while (command[i])
	{
		if (i == 0 && command[i] == '-')
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(command[i]))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit (2);
		}
		i++;
	}
	value = ft_atoi2(command);
	many_argument_error(next_command);
	exit (value);
}
