/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:15:58 by yeham             #+#    #+#             */
/*   Updated: 2023/02/09 16:14:55 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*assemble(t_list *dis)
{
	t_list	*head;
	char	*a;
	char	*temp;

	a = 0;
	if (dis == 0)
		return (a);
	temp = ft_strdup("");
	head = dis;
	while (head)
	{
		a = ft_strjoin(temp, head->content);
		free(temp);
		temp = a;
		head = head->next;
	}
	return (a);
}

char	*disassemble_assemble(char *str)
{
	t_list	*dis;
	t_list	*head;
	char	*result;

	dis = parsing(str);
	head = dis;
	result = assemble(head);
	free_list(dis);
	return (result);
}

void	blank_list_module(char **string, t_list *new)
{
	char	*temp;
	int		i;

	i = 0;
	while (string[i])
	{
		temp = disassemble_assemble(string[i]);
		ft_lstadd_back(&new, ft_lstnew(temp));
		i++;
	}
}
