/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:16 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 10:59:50 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <stdlib.h>

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

void	tokenize_string(t_list *list, char *string, int *index)
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

void	tokenize_space(t_list *list, char *string, int *index)
{
	int		start;
	int		length;
	char	*temp;
	int		space_len;

	start = (*index);
	while (string[(*index)] >= 9 && (string[(*index)] <= 13 \
	|| string[(*index)] == ' '))
		(*index)++;
	length = ((*index) - 1) - start + 1;
	temp = (char *)ft_calloc(length + 1, sizeof(char));
	space_len = 0;
	while (space_len < length)
		temp[space_len++] = ' ';
	partial_string(list, temp, 0, length);
	free(temp);
}
