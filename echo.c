/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:57:32 by yeham             #+#    #+#             */
/*   Updated: 2023/02/02 17:48:56 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
	printf("%s", (char *)head->next->content);
	if (head->next->next)
		printf(" ");
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
		printf("\n");
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
