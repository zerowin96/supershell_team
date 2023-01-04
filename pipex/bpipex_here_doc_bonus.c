/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bpipex_here_doc_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:24:59 by minsulee          #+#    #+#             */
/*   Updated: 2022/12/21 15:00:47 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "bpipex_bonus.h"

char	*pipex_heredoc_limiter(t_pipex *pipex)
{
	int		limiter_len;
	char	*limiter;

	limiter_len = ft_strlen(pipex->argv[2]);
	limiter = (char *)ml_malloc(sizeof(char) * (limiter_len + 2));
	ft_strlcpy(limiter, pipex->argv[2], limiter_len + 1);
	limiter[limiter_len] = '\n';
	limiter[limiter_len + 1] = 0;
	return (limiter);
}

void	pipex_heredoc(t_pipex *pipex, int *arg_index)
{
	char	*line;
	char	*limiter;
	int		limiter_len;

	limiter_len = ft_strlen(pipex->argv[2]);
	limiter = pipex_heredoc_limiter(pipex);
	ml_pipe(pipex->pipefd[1]);
	ml_write(1, "> ", 2);
	while (1)
	{
		line = get_next_line(0);
		if (line == 0 || ft_strncmp(line, limiter, limiter_len + 2) == 0)
			break ;
		ml_write(pipex->pipefd[1][WRITE], line, ft_strlen(line));
		ml_write(1, "> ", 2);
		free(line);
	}
	if (line)
		free(line);
	ml_close(pipex->pipefd[1][WRITE]);
	pipex->pipefd[1][WRITE] = 0;
	free(limiter);
	(*arg_index)++;
}
