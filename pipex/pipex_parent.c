/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:24:51 by minsulee          #+#    #+#             */
/*   Updated: 2022/12/21 17:32:35 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_split(char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			break ;
		index++;
	}
	if (envp[index] == 0)
		return (0);
	return (ft_split(&envp[index][5], ':'));
}

void	pipex_fd_pre(t_pipex *pipex, int index)
{
	pipex->pipefd[0][READ] = pipex->pipefd[1][READ];
	pipex->pipefd[0][WRITE] = 0;
	if (index < pipex->argc - 2 && pipex->argc != 4)
		ml_pipe(pipex->pipefd[1]);
	else
	{
		pipex->pipefd[1][WRITE] = 0;
		pipex->pipefd[1][READ] = 0;
	}
}

void	pipex_fd_post(t_pipex *pipex)
{
	if (pipex->pipefd[0][READ])
	{
		ml_close(pipex->pipefd[0][READ]);
		pipex->pipefd[0][READ] = 0;
	}
	if (pipex->pipefd[1][WRITE])
	{
		ml_close(pipex->pipefd[1][WRITE]);
		pipex->pipefd[1][WRITE] = 0;
	}
}

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ml_write(2, "not enough arguments : pipex\n", 30);
		return (1);
	}
	else if (argc > 5)
	{
		ml_write(2, "too many arguments : pipex\n", 28);
		return (1);
	}
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->paths = get_path_split(envp);
	pipex->pipefd[1][READ] = 0;
	pipex->pipefd[1][WRITE] = 0;
	return (0);
}

int	pipex_get_status(t_pipex *pipex, pid_t pid)
{
	int	index;
	int	ret_status;
	int	status;
	int	temp_pid;

	index = 0;
	status = 0;
	while (index < pipex->argc - 3)
	{
		temp_pid = waitpid(-1, &status, 0);
		if (pid == temp_pid)
			ret_status = status >> 8;
		index++;
	}
	return (ret_status);
}
