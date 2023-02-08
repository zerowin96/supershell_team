/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:57:32 by yeham             #+#    #+#             */
/*   Updated: 2023/02/08 19:07:35 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	only_n_check(char *string)
{
	int	i;

	i = 1;
	while (string[i])
	{
		if (string[i] != 'n')
			return (2);
		i++;
	}
	return (1);
}

void	print_and_check_space(t_list *head)
{
	ft_putstr_fd((char *)head->next->content, 1);
	if (head->next->next)
		write(1, " ", 1);
}

void	running_echo(t_list *head)
{
	int	flag;
	int	check;

	flag = 0;
	check = 0;
	while (head->next)
	{
		if (ft_strncmp(head->next->content, "-n", 2) == 0 && flag != 2)
		{
			flag = only_n_check(head->next->content);
			if (flag == 1)
				check = 1;
			else
				print_and_check_space(head);
		}
		else
		{
			flag = 2;
			print_and_check_space(head);
		}
		head = head->next;
	}
	if (check == 0)
		write(1, "\n", 1);
}

void	ft_echo(char *line, t_copy *env)
{
	t_list	*head;
	t_list	*temp;
	int		flag;
	int		check;

	flag = 0;
	check = 0;
	head = ft_lstnew(0);
	blank_list_module(env_split(line), env, head);
	temp = head;
	head = head->next;
	running_echo(head);
	free_list(temp);
}
