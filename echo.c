/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:57:32 by yeham             #+#    #+#             */
/*   Updated: 2023/02/02 15:16:50 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "test.h"
#include <stdio.h>

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
	temp = head;

	// char **test = env_split(line);
	// printf("vector_free vector 0 : %p\n", test);
	write(2, "ech0 : ", 7);
	system("leaks a.out | grep total");
	blank_list_module(env_split(line), env, head);
	// printf("vector_free vector 4 : %p\n", test);
	// vector_free(test);
	write(2, "ech1 : ", 7);
	system("leaks a.out | grep total");
	head = head->next;
	running_echo(head);
	free_list(temp);
	write(2, "ech2 : ", 7);
	system("leaks a.out | grep total");
}
