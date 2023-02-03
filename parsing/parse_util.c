/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:36:11 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 20:22:52 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*ft_strjoin2(const char *rep, const char *src, int start, int finish)
{
	char	temp[1];
	int		len;
	char	*ret_str;

	temp[0] = 0;
	if (!rep)
		rep = temp;
	len = (ft_strlen(src) - 1) - (finish - start + 1) \
	+ ft_strlen(rep) + 1;
	ret_str = (char *)ft_calloc(len, sizeof(char));
	ft_memmove(ret_str, src, start - 1);
	if (rep)
		ft_memmove(&ret_str[start - 1], rep, ft_strlen(rep));
	ft_memmove(&ret_str[ft_strlen(ret_str)], &src[finish + 1], \
	ft_strlen(&src[finish + 1]));
	return (ret_str);
}

void	free_empty(t_list *list)
{
	t_list	*cursor;
	t_list	*prev;

	cursor = list->next;
	prev = list;
	while (cursor)
	{
		if (cursor->content == 0 || *((char *)(cursor->content)) == 0)
		{
			prev->next = cursor->next;
			if (cursor->content)
				free(cursor->content);
			free(cursor);
			cursor = prev->next;
		}
		if (cursor)
		{
			cursor = cursor->next;
			prev = prev->next;
		}
	}
}

void	free_space(t_list *list)
{
	t_list	*cursor;
	t_list	*prev;

	cursor = list->next;
	prev = list;
	while (cursor)
	{
		if (cursor->content && *((char *)(cursor->content)) == ' ')
		{
			prev->next = cursor->next;
			if (cursor->content)
				free(cursor->content);
			free(cursor);
			cursor = prev->next;
		}
		if (cursor)
		{
			cursor = cursor->next;
			prev = prev->next;
		}
	}
}

void	quote_trim(t_list *list)
{
	t_list	*cursor;
	int		lendex;
	char	*new_string;

	cursor = list->next;
	while (cursor)
	{
		if (cursor->content && (((char *)(cursor->content))[0] == '\'' \
			|| ((char *)(cursor->content))[0] == '\"'))
		{
			lendex = ft_strlen((char *)cursor->content);
			new_string = (char *)ft_calloc(lendex - 1, sizeof(char));
			ft_memmove(new_string, \
				&(((char *)(cursor->content))[1]), lendex - 2);
			new_string[lendex] = 0;
			free(cursor->content);
			cursor->content = 0;
			cursor->content = new_string;
		}
		cursor = cursor->next;
	}
}