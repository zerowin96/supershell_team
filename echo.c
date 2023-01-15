/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:57:32 by yeham             #+#    #+#             */
/*   Updated: 2023/01/14 22:52:55 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_echo(char *line, t_list *node)
{
	t_list *head;
	t_list *new;

	new = ft_lstnew(0);
	head = node;
	while(head)
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
	printf("@@@@@@@@@@ echo test@@@@@@@\n");
	while (head->next)
	{
		printf("%s ", head->next->content);
		head = head->next;
	}
	printf("\n");
	printf("@@@@@@@@@@ echo test@@@@@@@\n");
}