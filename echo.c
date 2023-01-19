/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:57:32 by yeham             #+#    #+#             */
/*   Updated: 2023/01/19 14:51:44 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_echo(char *line, t_copy *env)
{
	char **echo_line;
	char *real_test;
	int flag;
	int i;
	t_list *a;
	t_list *head;

	flag = 0;
	a = ft_lstnew(0);
	echo_line = env_split(line);
	i = 0;
	while (echo_line[i])
	{
		real_test = disassemble_assemble(echo_line[i], env->cp_envp);
		ft_lstadd_back(&a, ft_lstnew(real_test));
		i++;
	}
	head = a->next;
	while (ft_strcmp(head->next->content, "-n") == 0)
	{
		head = head->next;
		flag = 1;
	}
	
	

	// head = head->next->next;


	// t_list	*prev = head;
	// while (prev)
	// {
	// 	if (prev->next)
	// 		if (prev->next->next == 0)
	// 		{
	// 			if (((char *)(prev->next->content))[0] == ' ' && ((char *)(prev->next->content))[1] == 0)
	// 			free(prev->next->content);
	// 			free(prev->next);
	// 			prev->next = 0;
	// 		}
	// 	prev = prev->next;
	// }


	printf("@@@@@@@@@@ echo test@@@@@@@\n");
	while (head->next)
	{
		printf("%s", head->next->content);
		head = head->next;
	}
	if (flag == 0)
		printf("\n");
	printf("@@@@@@@@@@ echo test@@@@@@@\n");
}
