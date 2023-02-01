/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:06:43 by yeham             #+#    #+#             */
/*   Updated: 2023/02/01 19:31:19 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (*ss1 && *ss2)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
	}
	return (*ss1 - *ss2);
}

void	export_print(char **sorted_envp)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (sorted_envp[i])
	{
		write(1, "declare -x ", 11);
		j = 0;
		flag = 0;
		while (sorted_envp[i][j])
		{
			write(1, &sorted_envp[i][j], 1);
			if (sorted_envp[i][j] == '=' && flag == 0)
			{
				write(1, "\"", 1);
				flag = 1;
			}
			j++;
		}
		if (flag == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

char	**only_sort(char **string)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (string[i])
	{
		j = 0;
		while (string[j + 1])
		{
			if (ft_strcmp(string[j], string[j + 1]) > 0)
			{
				temp = string[j];
				string[j] = string[j + 1];
				string[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (string);
}

void	sort_and_print(char **string)
{
	int		i;
	int		j;
	char	*temp;
	char	**sorted_envp;

	i = 0;
	sorted_envp = 0;
	while (string[i])
	{
		sorted_envp = vector_add(sorted_envp, string[i]);
		i++;
	}
	only_sort(sorted_envp);
	export_print(sorted_envp);
	//sorted_envp 프리 예정
}
