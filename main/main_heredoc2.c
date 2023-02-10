/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:03:37 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/10 10:43:17 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*get_filename(void)
{
	char	*string;
	int		index;
	int		len;

	string = ft_strjoin("/tmp/", "100000000000.tmp");
	while (access(string, F_OK) == 0)
	{
		index = 4;
		string[5]++;
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
