/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:15:28 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/10 11:38:00 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_list	*vector_to_list(char ***vector)
{
	t_list	*list;
	t_list	*temp;
	int		index;

	list = ft_lstnew(0);
	if (!vector || !(*vector))
	{
		free_list(list);
		return (0);
	}
	index = 0;
	while ((*vector)[index])
	{
		ft_lstadd_back(&list, ft_lstnew((*vector)[index]));
		index++;
	}
	temp = 0;
	if (list->next)
		temp = list->next;
	free(list->content);
	list->content = 0;
	free(list);
	list = 0;
	return (temp);
}

char	**list_to_vector(t_list *list)
{
	char	**vector;

	vector = 0;
	if (!list->content || (ft_strlen(list->content) == 1 \
	&& ((char *)(list->content))[0] == ' '))
		list = list->next;
	while (list)
	{
		vector = vector_add(vector, list->content);
		list = list->next;
	}
	return (vector);
}

int	ml_iswhite(char c)
{
	if (c == ' ')
		return (1);
	else if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

void	list_tie_h(t_list **prev, t_list **temp)
{
	char	*temp_string;

	if (((*temp)->content == 0 || (*prev)->content == 0) \
		|| !(ft_strncmp((*prev)->content, " ", 2) \
		&& ft_strncmp((*temp)->content, " ", 2)))
		(*prev) = (*temp);
	else
	{
		temp_string = ft_strjoin((*prev)->content, (*temp)->content);
		free ((*prev)->content);
		(*prev)->content = temp_string;
		(*prev)->next = (*temp)->next;
		free((*temp)->content);
		free((*temp));
	}
}

void	list_tie(t_list *temp)
{
	t_list	*tie_temp;
	t_list	*tie_prev;

	if (!temp->next)
		return ;
	tie_temp = temp->next->next;
	tie_prev = temp->next;
	while (tie_temp)
	{
		list_tie_h(&tie_prev, &tie_temp);
		tie_temp = tie_prev->next;
	}
}
