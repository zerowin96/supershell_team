/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:36:11 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/08 22:11:46 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*ft_strjoin2(const char *ref, const char *src, int start, int finish)
{
	char	temp[1];
	int		len;
	char	*ret_str;

	temp[0] = 0;
	if (!ref)
		ref = temp;
	len = (ft_strlen(src) - 1) - (finish - start + 1) \
	+ ft_strlen(ref) + 1;
	ret_str = (char *)ft_calloc(len, sizeof(char));
	ft_memmove(ret_str, src, start - 1);
	if (ref)
		ft_memmove(&ret_str[start - 1], ref, ft_strlen(ref));
	ft_memmove(&ret_str[ft_strlen(ret_str)], &src[finish + 1], \
	ft_strlen(&src[finish + 1]));
	return (ret_str);
}

void	free_empty(t_list *list)
{
	t_list	*cursor;
	t_list	*prev;

	if (!list)
		return ;
	cursor = list->next;
	prev = list;
	while (cursor)
	{
		if (cursor->content == 0 || !(((char *)(cursor->content))[0]))
		{
		// 	prev->next = cursor->next;
		// 	free(cursor);
		// }
		// else if (((char *)(cursor->content))[0] == 0)
		// {
			prev->next = cursor->next;
			if (cursor->content)
				free(cursor->content);
			cursor->content = 0;
			free(cursor);
		}
		else
			prev = prev->next;
		cursor = prev->next;
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
		if (cursor->content && ft_strncmp((cursor->content), " ", 2) == 0)
		{
			prev->next = cursor->next;
			if (cursor->content)
				free(cursor->content);
			free(cursor);
			cursor = prev->next;
		}
		else if (cursor)
		{
			cursor = cursor->next;
			prev = prev->next;
		}
	}
}

void	quote_trim_partial(t_list *list)
{
	t_list	*cursor;
	int		lendex;
	char	*new_string;

	cursor = list;
	if (cursor == 0)
		return ;
	lendex = ft_strlen((char *)cursor->content);
	if (lendex < 2 ||
	(((char *)(cursor->content))[0] != ((char *)(cursor->content))[lendex - 1]))
		;
	// else if (((char *)(cursor->content))[0] != ((char *)(cursor->content))[lendex - 1])
	// 	;
	else if ((((char *)(cursor->content))[0] == '\'' \
		|| ((char *)(cursor->content))[0] == '\"'))
	{
		new_string = (char *)ft_calloc(lendex - 1, sizeof(char));
		ft_memmove(new_string, \
			&(((char *)(cursor->content))[1]), lendex - 2);
		new_string[lendex - 2] = 0;
		free(cursor->content);
		cursor->content = new_string;
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
		while (cursor && !cursor->content)
			cursor = cursor->next;
		if (cursor == 0)
			break ;
		quote_trim_partial(cursor);
		cursor = cursor->next;
		// if (cursor == 0)
		// 	break ;
		// lendex = ft_strlen((char *)cursor->content);
		// if (lendex < 2)
		// 	;
		// else if (((char *)(cursor->content))[0] != ((char *)(cursor->content))[lendex - 1])
		// 	;
		// else if ((((char *)(cursor->content))[0] == '\'' \
		// 	|| ((char *)(cursor->content))[0] == '\"'))
		// {
		// 	new_string = (char *)ft_calloc(lendex - 1, sizeof(char));
		// 	ft_memmove(new_string, \
		// 		&(((char *)(cursor->content))[1]), lendex - 2);
		// 	new_string[lendex - 2] = 0;
		// 	free(cursor->content);
		// 	cursor->content = new_string;
		// }
		// cursor = cursor->next;
	}
}