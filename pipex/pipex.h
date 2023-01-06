/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:24:12 by minsulee          #+#    #+#             */
/*   Updated: 2023/01/05 14:50:17 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define WRITE 1
# define READ 0
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**paths;
	int		(*pipefd)[2];
}	t_pipex;

char	*get_next_line(int fd);
int		child_process(int pipefd[2][2], char *cmd, char **paths, char **envp);
void	ft_split_free(char **string);
void	pipex_clone(t_pipex *pipex, pid_t *pid, int index);
char	**get_path_split(char **envp);
void	pipex_fd_pre(t_pipex *pipex, int index);
void	pipex_fd_post(t_pipex *pipex);
int		pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
int		pipex_get_status(t_pipex *pipex, pid_t pid);
#endif
