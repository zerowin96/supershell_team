/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_util_general.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:21:53 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 18:38:59 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	pipe_exists(t_list *line)
{
	t_list	*temp;

	temp = line;
	while (temp)
	{
		if (ft_strncmp(((char *)temp->content), "|", 2) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	sep_kind(t_list *node)
{
	if (ft_strncmp(node->content, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(node->content, "<<", 3) == 0)
		return (2);
	else if (ft_strncmp(node->content, ">", 2) == 0)
		return (3);
	else if (ft_strncmp(node->content, ">>", 3) == 0)
		return (4);
	else if (ft_strncmp(node->content, "|", 2) == 0)
		return (5);
	return (0);
}

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list->next;
		if (list->content)
		{
			free(list->content);
			list->content = 0;
		}
		free(list);
		list = temp;
	}
}

int	builtin_check(char *line, t_list *node, t_copy *e, char *string)
{
	int	index;

	index = 0;
	if (ft_strncmp(string, "echo\0", 5) == 0)
		index = 1;
	else if (ft_strncmp(string, "cd\0", 3) == 0)
		index = 2;
	else if (ft_strncmp(string, "pwd\0", 4) == 0)
		index = 3;
	else if (ft_strncmp(string, "export\0", 7) == 0)
		index = 4;
	else if (ft_strncmp(string, "unset\0", 6) == 0)
		index = 5;
	else if (ft_strncmp(string, "env\0", 4) == 0)
		index = 6;
	else if (ft_strncmp(string, "exit\0", 5) == 0)
		index = 7;
	return (index);
}
