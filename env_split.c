/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:30:49 by minsulee          #+#    #+#             */
/*   Updated: 2023/01/13 15:20:47 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	get_section(char *string, int *index, int *start, int *finish)
{
	while (string[*index] == ' ')
		(*index)++;
	// *start = (*index)++;
	if (string[*index] == 0)
		return ;
	if (string[*index] && string[*index] != ' ')
	{
		*start = *index;
		while (string[*index] != ' ' && string[*index])
		{
			if (string[*index] == '\'')
			{
				(*index)++;
				while (string[*index] != '\'' && string[*index])
					(*index)++;
				(*index)++;
			}
			else if (string[*index] == '\"')
			{
				(*index)++;
				while (string[*index] != '\"' && string[*index])
					(*index)++;
				(*index)++;
			}
			else
				(*index)++;
		}
		*finish = *index;
	}
}
static char	**ft_linkedlist_to_split(t_list *list)
{
	char	**help2;
	int		index;
	t_list	*temp;

	help2 = (char **)ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
	index = 0;
	temp = list;
	while (list)
	{
		temp = list->next;
		help2[index++] = (char *)(list->content);
		free(list);
		list = temp;
	}
	return (help2);
}

static char	**pipex_split_quote_parse(t_list *list, char *string)
{
	int		index;
	int		start;
	int		finish;
	char	*help;

	index = 0;
	start = 0;
	finish = 0;
	help = 0;
	while (string[index])
	{
		get_section(string, &index, &start, &finish);
		help = (char *)ft_calloc(finish - start + 1, sizeof(char));
		ft_memmove(help, &string[start], finish - start);
		ft_lstadd_back(&list, ft_lstnew(help));
		if (string[index] == 0)
			break ;
	}
	return (ft_linkedlist_to_split(list));
}

char	**env_split(char *command)
{
	t_list	*list;
	int		index;
	int		count;
	char	**res;

	list = 0;
	index = 0;
	count = 0;
	while (command[index])
		if (command[index++] == '\'')
			count++;
	if (count % 2 != 0)
	{
		ft_putstr_fd("Invalid option (quote)\n", 2);
		exit (1);
	}
	res = pipex_split_quote_parse(list, command);
	return (res);
}
