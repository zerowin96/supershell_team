/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bpipex_junction_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:24:56 by minsulee          #+#    #+#             */
/*   Updated: 2022/12/21 15:00:46 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "bpipex_bonus.h"

void	pipex_fd_outfile(t_pipex *pipex)
{
	if (ft_strncmp(pipex->argv[1], "here_doc\0", 9) == 0)
		pipex->pipefd[1][WRITE] = open(pipex->argv[pipex->argc - 1], \
		O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		pipex->pipefd[1][WRITE] = open(pipex->argv[pipex->argc - 1], \
		O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex->pipefd[1][WRITE] < 0)
	{
		perror("output file error");
		exit (1);
	}
}

void	pipex_fd_infile(t_pipex *pipex)
{
	pipex->pipefd[0][READ] = open(pipex->argv[1], O_RDONLY, 0644);
	if (pipex->pipefd[0][READ] < 0)
	{
		perror("input file error");
		exit (1);
	}
}

void	pipex_clone(t_pipex *pipex, pid_t *pid, int index)
{
	*pid = fork();
	if (*pid == 0)
	{
		if (index == pipex->argc - 2 || pipex->argc == 3)
			pipex_fd_outfile(pipex);
		else if (index == 2 || pipex->argc == 3)
			pipex_fd_infile(pipex);
		child_process(pipex->pipefd, pipex->argv[index], \
			pipex->paths, pipex->envp);
		exit(1);
	}
	else if (*pid < 0)
	{
		perror("error on function *fork*");
		exit(1);
	}
}
