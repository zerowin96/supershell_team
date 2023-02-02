/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:55:59 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 18:27:47 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	status_return(int pid)
{
	int	ret_status;
	int	status;
	int	temp_pid;

	ret_status = 0;
	temp_pid = 1;
	while (temp_pid >= 0)
	{
		parent_handle_signal();
		temp_pid = waitpid(-1, &status, 0);
		if (temp_pid == pid)
			ret_status = status >> 8;
		if (temp_pid < 0)
			break ;
	}
	return (ret_status);
}

void	command_run_fd_prev(t_list *temp, int (*fd)[2])
{
	fd[PREV][READ] = fd[NEXT][READ];
	fd[PREV][WRITE] = 0;
	if (pipe_exists(temp))
		pipe(fd[NEXT]);
	else
	{
		fd[NEXT][WRITE] = 0;
		fd[NEXT][READ] = 0;
	}
}

void	command_run_fd_post(int (*fd)[2])
{
	if (fd[PREV][READ])
	{
		close(fd[PREV][READ]);
		fd[PREV][READ] = 0;
	}
	if (fd[NEXT][WRITE])
	{
		close(fd[NEXT][WRITE]);
		fd[NEXT][WRITE] = 0;
	}
}

int	command_run(t_list* list, char *line, t_copy *e)
{
	int		pipefd[2][2];
	int		pid;

	pipefd[NEXT][READ] = 0;
	pipefd[NEXT][WRITE] = 0;
	while (list)
	{
		command_run_fd_prev(list, pipefd);
		pid = fork();
		if (pid == 0)
			child_process(list, line, e, pipefd);
		else if (pid < 0)
		{
			perror("fork failed");
			exit (1);
		}
		command_run_fd_post(pipefd);
		while (list && ft_strncmp(((char *)list->content), "|", 2) != 0)
			list = list->next;
		if (list)
			list = list->next;
	}
	return (status_return(pid));
}
