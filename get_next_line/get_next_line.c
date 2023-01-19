/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:51:41 by minsulee          #+#    #+#             */
/*   Updated: 2022/08/12 16:04:55 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (src[count] != 0)
		count++;
	if (dstsize == 0)
		return (count);
	while ((src[index] != 0) && (1 < dstsize))
	{
		dst[index] = src[index];
		index++;
		dstsize--;
	}
	dst[index] = 0;
	return (count);
}

size_t	free_all(t_list *head)
{
	t_list	*next_list;

	while (head)
	{
		next_list = head->next;
		head->next = 0;
		head->content[0] = 0;
		free(head);
		head = next_list;
	}
	return (0);
}

t_list	*head_initialize(void)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (head == 0)
		return (0);
	head->next = 0;
	head->content[0] = 0;
	return (head);
}

char	*find_nl_print(int fd, char *buffer, t_list *head)
{
	ssize_t		str_len;
	ssize_t		index;

	while (1)
	{
		str_len = read(fd, buffer, BUFFER_SIZE);
		if (str_len < 0)
			return ((char *)free_all(head));
		if (str_len == 0)
			return (read_free_bufferpush_return(head, 0, 0));
		buffer[str_len] = 0;
		index = -1;
		while (buffer[++index])
		{
			if (buffer[index] == '\n')
			{
				if (list_gen_with_newstr(buffer, head, index + 1) == 0)
					return (0);
				return (read_free_bufferpush_return(head, buffer, index));
			}
		}
		if (list_gen_with_newstr(buffer, head, str_len) == 0)
			return (0);
		buffer[0] = 0;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		index;
	t_list		*head;

	if (fd < 0 || read(fd, NULL, 0) < 0)
		return (0);
	head = head_initialize();
	if (head == 0)
		return (0);
	if (buffer[0])
	{
		index = 0;
		while (buffer[index])
		{
			if (buffer[index] == '\n')
				return (buffer_printer(buffer, index, head));
			index++;
		}
		if (list_gen_with_newstr(buffer, head, index + 1) == 0)
			return (0);
		ft_strlcpy(buffer, buffer + index, BUFFER_SIZE);
	}
	return (find_nl_print(fd, buffer, head));
}
