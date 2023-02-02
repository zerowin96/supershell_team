/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minsu_test_tokenize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:27:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 18:43:20 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list *parsing(char *line, char **envp)
{
	t_list	*list;
	t_list	*now;

	list = ft_lstnew(0);
	tokenize(list, line);
	if (quote_check(list))
		return (0);
	env_expansion(list, envp);
	return (list);
}

char	*listjoin(t_list *list)
{
	t_list	*cursor;
	char	*temp = 0;
	char	*temp1 = 0;

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

t_list *first_parsing(char **line, char **envp, int prev_result)
{
	t_list	*list;
	t_list	*now;
	char	*temp;

	list = ft_lstnew(0);
	tokenize(list, *line);
	free(*line);
	if (quote_check(list))
	{
		return (0);
	}
	qmark_expansion(list, prev_result);
	env_expansion(list, envp);

	temp = listjoin(list);
	free_list(list);
	list = ft_lstnew(0);
	tokenize(list, temp);
	*line = temp;
	return (list);
}
