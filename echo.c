/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:57:32 by yeham             #+#    #+#             */
/*   Updated: 2023/02/01 18:59:39 by minsulee         ###   ########seoul.kr  */
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

int	flag_check(int flag, char *string)
{
	int	check;

	check = 0;
	if (flag == 1)
		check = 1;
	else if (flag == 2)
		printf("%s ", string);
	return (check);
}

void check_print(int check)
{
	if (check == 0)
		printf("\n");
	if (check == 1)
		printf("\b");
}

void	ft_echo(char *line, t_copy *env)
{
	t_list	*head;
	int		flag;
	int		check;

	flag = 0;
	check = 0;
	head = ft_lstnew(0);
	blank_list_module(env_split(line), env, head);
	head = head->next;
	while (head->next)
	{
		if (ft_strncmp(head->next->content, "-n", 2) == 0 && flag != 2)
		{
			flag = only_n_check(head->next->content);
			check = flag_check(flag, head->next->content);
		}
		else
		{
			printf("%s ", head->next->content);
			flag = 2;
		}
		head = head->next;
	}
	check_print(check);
	free_list(head);
}
