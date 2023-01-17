/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:57:32 by yeham             #+#    #+#             */
/*   Updated: 2023/01/17 10:15:30 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_echo(char *line, t_list *node)
{
	t_list *head;
	t_list *new;

	new = ft_lstnew(0);
	head = node;
	while (head && ((char *)(head->content))[0] != '|')
	{
		ft_lstadd_back(&new, ft_lstnew(head->content));
		head = head->next;
	}
	head = new->next;
	new = new->next;
	while (new)
	{
		quote_trim(new);
		free_empty(new);
		new = new->next;
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
	printf("\n");
	printf("@@@@@@@@@@ echo test@@@@@@@\n");
}
