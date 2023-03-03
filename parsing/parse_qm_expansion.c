/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_qm_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:33:57 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 09:28:54 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	qmark_expansion_string(char **string, int previous_code)
{
	int		start;
	int		index;
	int		finish;
	char	*temp[3];

	index = 0;
	if ((*string)[index] == '\'')
		return ;
	while ((*string)[index])
	{
		if ((*string)[index] == '$' && (*string)[index + 1] == '?')
		{
			start = ++index;
			finish = index;
			temp[1] = ft_itoa(previous_code);
			temp[2] = ft_strjoin2(temp[1], *string, start, finish);
			free(*string);
			*string = temp[2];
			index = (start - 1) + ft_strlen(temp[1]);
			free(temp[1]);
			temp[1] = 0;
		}
		else
			index++;
	}
}

void	qmark_expansion(t_list *list, int pres)
{
	t_list	*cursor;

	cursor = list->next;
	while (cursor)
	{
		qmark_expansion_string(((char **)&(cursor->content)), pres);
		if (cursor)
			cursor = cursor->next;
	}
	free_empty(list);
}
