/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:00:11 by minsulee          #+#    #+#             */
/*   Updated: 2022/08/12 16:04:51 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (s == 0)
		return (0);
	count = 0;
	while (*s != 0)
	{
		count++;
		s++;
	}
	return (count);
}

char	*buffer_printer(char *buffer, size_t index, t_list *head)
{
	char	*ret_str;

	ret_str = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (ret_str == 0)
		return ((char *)free_all(head));
	ft_strlcpy(ret_str, buffer, index + 2);
	ft_strlcpy(buffer, buffer + index + 1, BUFFER_SIZE);
	free_all(head);
	return (ret_str);
}

void	content_copy(t_list *head, size_t str_len, char *ret_str)
{
	size_t	index;
	t_list	*temp;

	ret_str[str_len] = 0;
	str_len = 0;
	temp = head;
	while (temp)
	{
		index = 0;
		while ((temp->content)[index])
			ret_str[str_len++] = (temp->content)[index++];
		temp = temp->next;
	}
	free_all(head);
}

char	*read_free_bufferpush_return(t_list *head, char *buffer, ssize_t index)
{
	char	*ret_str;
	t_list	*temp;
	size_t	str_len;

	if (buffer)
		ft_strlcpy(buffer, buffer + index + 1, BUFFER_SIZE);
	str_len = 0;
	temp = head;
	while (temp)
	{
		str_len = str_len + ft_strlen(temp->content);
		temp = temp->next;
	}
	if (str_len == 0)
		return ((char *)free_all(head));
	ret_str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (ret_str == 0)
		return ((char *)free_all(head));
	content_copy(head, str_len, ret_str);
	return (ret_str);
}

size_t	list_gen_with_newstr(char *str, t_list *head, size_t len)
{
	t_list	*temp;

	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = (t_list *)malloc(sizeof(t_list) * 1);
	if (temp->next == 0)
		return (free_all(head));
	temp = temp->next;
	temp->next = 0;
	ft_strlcpy(temp->content, str, len + 1);
	return (1);
}
