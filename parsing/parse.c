/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:27:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 14:58:15 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <stdlib.h>

t_list	*parsing(char *line)
{
	t_list	*list;

	list = ft_lstnew(0);
	tokenize_2(list, line);
	return (list);
}

char	*listjoin(t_list *list)
{	
	t_list	*cursor;
	char	*temp;
	char	*temp1;

	temp = 0;
	temp1 = 0;
	cursor = list->next;
	temp1 = (char *)ft_calloc(1, sizeof(char));
	while (cursor)
	{
		temp = ft_strjoin(temp1, cursor->content);
		free(temp1);
		temp1 = temp;
		cursor = cursor->next;
	}
	return (temp);
}

t_list	*first_parsing(char **line)
{
	t_list	*list;

	list = ft_lstnew(0);
	tokenize(list, *line);
	if (quote_check(list))
	{
		free_list(list);
		list = 0;
		return (0);
	}
	return (list);
}
