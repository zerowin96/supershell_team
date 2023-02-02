/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:03:37 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 19:12:57 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*get_filename(void)
{
	char	*string;
	int		index;
	int		len;

	string = (char *)ft_calloc(17, sizeof(char));
	ft_memmove(string, "100000000000.tmp", 16);
	while (access(string, F_OK) == 0)
	{
		index = -1;
		string[0]++;
		len = ft_strlen(string);
		while (++index < len)
		{
			if (string[index] == 127)
			{
				string[index] = '0';
				string[index + 1]++;
				if (index + 1 == len)
					len++;
			}
			if (string[index] < '0' && string[index] != '.')
				string[index] = '0';
		}
	}
	return (string);
}
