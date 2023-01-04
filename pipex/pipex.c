/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:24:49 by minsulee          #+#    #+#             */
/*   Updated: 2022/12/21 17:21:20 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2][2];
	t_pipex	pipex;
	int		pid;
	int		arg_index;

	pipex.pipefd = pipefd;
	if (pipex_init(&pipex, argc, argv, envp))
		return (1);
	arg_index = 2;
	while (arg_index < argc - 1)
	{
		pipex_fd_pre(&pipex, arg_index);
		pipex_clone(&pipex, &pid, arg_index);
		pipex_fd_post(&pipex);
		arg_index++;
	}
	ft_split_free(pipex.paths);
	return (pipex_get_status(&pipex, pid));
}
