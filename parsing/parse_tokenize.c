/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:16 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/03 13:33:43 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	partial_string(t_list *list, char *string, int start, int finish)
{
	char	*temp;

	temp = (char *)ft_calloc(finish - start + 2, sizeof(char));
	ft_memmove(temp, &string[start], finish - start + 1);
	ft_lstadd_back(&list, ft_lstnew(temp));
}

void	tokenize_expansion(t_list *list, char *string, int *index)
{
	int	start;
	int	finish;

	start = (*index);
	while (string[(*index)] != ' ' && string[(*index)] && \
	is_separator(&string[(*index)]) == 0)
	{
		(*index)++;
		if (string[(*index)] == '$')
			break ;
	}
	finish = (*index) - 1;
	partial_string(list, string, start, finish);
	(*index)--;
}

void	tokenize_space(t_list *list, char *string, int *index)
{
	int	start;
	int	finish;

	start = (*index);
	while (string[(*index)] != ' ' && string[(*index)] && \
	is_separator(&string[(*index)]) == 0 && string[(*index)] != '$')
		(*index)++;
	finish = (*index) - 1;
	partial_string(list, string, start, finish);
	(*index)--;
}

void	tokenize_separator(t_list *list, char *string, int *index)
{
	int	start;
	int	finish;

	start = (*index);
	(*index) += (is_separator(&string[(*index)]) - 1);
	finish = (*index);
	partial_string(list, string, start, finish);
}

void	tokenize(t_list *list, char *string)
{
	int		index;

	index = 0;
	while (string[index])
	{
		if ((string[index] >= 9 && string[index] <= 13) || string[index] == ' ')
		{
			if (index)
				partial_string(list, " ", 0, 1);
			while (string[index] >= 9 && (string[index] <= 13 \
			|| string[index] == ' '))
				index++;
		}
		if (is_separator(&string[index]))
			tokenize_separator(list, string, &index);
		else if (string[index] && string[index] == '$')
			tokenize_expansion(list, string, &index);
		else if (string[index] && string[index] != ' ')
			tokenize_space(list, string, &index);
		if (string[index] == 0)
			break ;
		index++;
	}
}
