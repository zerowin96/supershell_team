/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenize2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:56:44 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 14:07:39 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	tokenize_2(t_list *list, char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if ((string[index] >= 9 && string[index] <= 13) || string[index] == ' ')
			tokenize_space(list, string, &index);
		if (is_separator(&string[index]))
			tokenize_separator(list, string, &index);
		else if (string[index] && string[index] == '$')
			tokenize_expansion(list, string, &index);
		else if (string[index] && string[index] != ' ')
			tokenize_string(list, string, &index);
		if (string[index] == 0)
			break ;
		index++;
	}
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
			tokenize_string(list, string, &index);
		if (string[index] == 0)
			break ;
		index++;
	}
}
