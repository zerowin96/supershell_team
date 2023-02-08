/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:15:58 by yeham             #+#    #+#             */
/*   Updated: 2023/02/08 20:45:10 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*assemble(t_list *dis)
{
	t_list	*head;
	char	*a;
	char	*temp;

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

char	*disassemble_assemble(char *str, char **envp)
{
	t_list	*dis;
	t_list	*head;
	char	*a;

	dis = parsing(str, envp);
	head = dis;
	quote_trim(head);
	free_empty(head);
	a = assemble(head);
	free_list(dis);
	return (a);
}

void	blank_list_module(char **string, t_copy *env, t_list *new)
{
	char	*temp;
	int		i;

	i = 0;
	// printf("blank list module\n");
	while (string[i])
	{
		temp = disassemble_assemble(string[i], env->cp_envp);
		ft_lstadd_back(&new, ft_lstnew(temp));
		free(string[i]);
		i++;
	}
	free(string);
}
