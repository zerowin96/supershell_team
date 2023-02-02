/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_split_sep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:25 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 19:02:36 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	command_split_separator_read(t_list *temp, int (*fd)[2], int sep)
{
	fd[PREV][READ] = open(((char *)(temp->next->content)), O_RDONLY);
	if (fd[PREV][READ] < 0)
	{
		if (sep == 1)
			perror("file not found");
		else
			perror("heredoc temp file error");
		return (1);
	}
	return (0);
}

int	command_split_separator_write(t_list *temp, int (*fd)[2], int sep)
{
	if (sep == 3)
		fd[NEXT][WRITE] = open(((char *)(temp->next->content)), \
		O_RDWR | O_TRUNC | O_CREAT, 0644);
	else
		fd[NEXT][WRITE] = open(((char *)(temp->next->content)), \
		O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd[NEXT][WRITE] < 0)
		return (perror("file open error"), 1);
	return (0);
}

int	command_split_separator(t_list **temp, int (*fd)[2], int sep)
{
	if (((char *)((*temp)->next->content))[0] == ' ')
		(*temp) = (*temp)->next;
	if (sep == 1 || sep == 2)
	{
		if (command_split_separator_read((*temp), fd, sep))
			return (1);
	}
	else
	{
		if (command_split_separator_write((*temp), fd, sep))
			return (1);
	}
	return (0);
}
