/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:49:16 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 12:02:01 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*string_connect(char *dst, char *src)
{
	int		len1;
	int		len2;
	char	*temp;

	len1 = 0;
	len2 = 0;
	if (dst)
		len1 = ft_strlen(dst);
	if (src)
		len2 = ft_strlen(src);
	temp = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (len1)
		ft_memmove(temp, dst, len1);
	if (len2)
		ft_memmove(&temp[len1], src, len2);
	if (dst)
		free(dst);
	return (temp);
}

void	command_split_delspace(char **temp_string)
{
	int	len;

	while (1)
	{
		len = ft_strlen((*temp_string));
		if (len == 0)
			break ;
		if ((*temp_string)[len - 1] == ' ')
			(*temp_string)[len - 1] = 0;
		else
			break ;
	}
}

void	command_split_h(char ***command, char **string, char *addition)
{
	(*command) = vector_add((*command), addition);
	(*string) = string_connect((*string), addition);
}

int	command_split(t_list *temp, int (*fd)[2], char ***command, char **string)
{
	int	sep;

	while (temp && ((char *)(temp->content))[0] != '|')
	{
		sep = sep_kind(temp);
		if (((char *)(temp->content))[0] == ' ')
		{
			if (*command)
				command_split_h(command, string, " ");
		}
		else if (sep >= 1 && sep <= 4)
		{
			if (command_split_separator(&temp, fd, sep))
				return (1);
			temp = temp->next;
		}
		else
			command_split_h(command, string, (temp->content));
		temp = temp->next;
	}
	return (command_split_delspace(string), 0);
}
