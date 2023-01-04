/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bpipex_gnl_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:27:18 by minsulee          #+#    #+#             */
/*   Updated: 2022/12/21 15:00:48 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "bpipex_bonus.h"

void	buffer_pull(char *buffer)
{
	int	index;
	int	temp;

	index = 0;
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (buffer[index] == 0)
		buffer[0] = 0;
	else
	{
		index++;
		temp = 0;
		while (buffer[temp + index])
		{
			buffer[temp] = buffer[temp + index];
			temp++;
		}
		buffer[temp] = 0;
	}
}

void	string_move(char *dest, char *pre, char *bf)
{
	int	index;

	index = 0;
	while (pre[index])
	{
		dest[index] = pre[index];
		index++;
	}
	dest = &dest[index];
	index = 0;
	while (bf[index])
	{
		dest[index] = bf[index];
		index++;
		if (dest[index - 1] == '\n')
			break ;
	}
	dest[index] = 0;
}

char	*string_connect(char *pre, char *bf)
{
	int		prelen;
	int		bflen;
	char	*retstr;

	prelen = ft_strlen(pre);
	bflen = 0;
	while (bf[bflen] && bf[bflen] != '\n')
		bflen++;
	if (bf[bflen] == '\n')
		bflen++;
	retstr = (char *)ml_malloc(sizeof(char) * (prelen + bflen + 1));
	if (retstr == 0)
	{
		free(pre);
		pre = 0;
		return (0);
	}
	string_move(retstr, pre, bf);
	buffer_pull(bf);
	free(pre);
	pre = 0;
	return (retstr);
}

char	*gnl_helper(int fd, char *string, char *buffer)
{
	int	length;
	int	index;

	while (1)
	{
		length = ml_read(fd, buffer, 7);
		buffer[length] = 0;
		if (length == 0 && *string == 0)
		{
			free(string);
			string = 0;
			return (0);
		}
		else if (length == 0)
			return (string_connect(string, buffer));
		index = 0;
		while (index < 7 && buffer[index])
		{
			if (buffer[index] == '\n' || buffer[index] == 0)
				return (string_connect(string, buffer));
			index++;
		}
		string = string_connect(string, buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[8];
	int			index;
	char		*string;

	if (ml_read(fd, NULL, 0) < 0)
	{
		buffer[0] = 0;
		return (0);
	}
	string = (char *)ml_malloc(sizeof(char) * 1);
	if (string == 0)
		return (0);
	string[0] = 0;
	index = 0;
	if (buffer[0] != 0)
	{
		while (index <= 7 && buffer[index])
		{
			if (buffer[index] == '\n')
				return (string_connect(string, buffer));
			index++;
		}
		string = string_connect(string, buffer);
	}
	return (gnl_helper(fd, string, buffer));
}
