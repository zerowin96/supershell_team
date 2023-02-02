/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_merge_space.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:15:58 by yeham             #+#    #+#             */
/*   Updated: 2023/02/01 21:20:27 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*assemble(t_list *dis)
{
	t_list	*head;
	char	*a;

	a = ft_strdup("");
	head = dis;
	while (head)
	{
		a = ft_strjoin(a, head->content);
		head = head->next;
	}
	return (a);
}

char	*disassemble_assemble(char *fuck, char **envp)
{
	t_list	*dis;
	t_list	*head;
	char	*a;

	dis = ft_lstnew(0);
	dis = parsing(fuck, envp);
	head = dis;
	quote_trim(head);
	free_empty(head);
	a = assemble(head);
	return (a);
}

void	blank_list_module(char **string, t_copy *env, t_list *new)
{
	char	*temp;
	int		i;

	i = 0;
	while (string[i])
	{
		temp = disassemble_assemble(string[i], env->cp_envp);
		ft_lstadd_back(&new, ft_lstnew(temp));
		free(string[i]);
		i++;
	}
	free(string);
}
