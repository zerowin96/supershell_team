/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bpipex_child_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:25:11 by minsulee          #+#    #+#             */
/*   Updated: 2022/12/21 16:37:45 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "bpipex_bonus.h"

int	check_access_h(char *name, char *path, int permission)
{
	char	*temp;
	char	*temp2;
	int		index;

	temp2 = 0;
	temp = 0;
	index = 0;
	if (name == 0)
		return (0);
	if (path != 0)
	{
		temp2 = ft_strjoin(path, "/");
		temp = ft_strjoin(temp2, name);
		free(temp2);
	}
	if (path == 0)
		temp = name;
	if (access(temp, permission) == 0)
		index = 1;
	if (path != 0)
	{
		free(temp);
		temp = 0;
	}
	return (index);
}

int	check_access(char *name, char **paths, int permission)
{
	int	index;

	index = 0;
	while (paths[index])
	{
		if (check_access_h(name, paths[index], permission))
			return (index + 2);
		index++;
	}
	if (check_access_h(name, 0, permission))
	{
		if (name[0] == '.' && name[1] == '/')
			return (1);
		else if (name[0] == '/')
			return (1);
	}
	return (-1);
}

void	pipex_child_fd(int pipefd[2][2])
{
	ml_close(pipefd[1][READ]);
	ml_dup2(pipefd[0][READ], 0);
	ml_dup2(pipefd[1][WRITE], 1);
	ml_close(pipefd[0][READ]);
	ml_close(pipefd[1][WRITE]);
}

int	child_process(int pipefd[2][2], char *command, char **paths, char **envp)
{
	char	**string;
	int		index;
	int		err_check;

	pipex_child_fd(pipefd);
	err_check = 0;
	string = ft_split(command, ' ');
	index = check_access(string[0], paths, X_OK);
	if (index == 1)
		err_check = execve(string[0], string, envp);
	else if (index > 1)
		err_check = execve(ft_strjoin(paths[index - 2], \
		ft_strjoin("/", string[0])), string, envp);
	if (err_check < 0)
		return (perror("error on function *execve*"), 1);
	ft_putstr_fd(string[0], 2);
	ml_write(2, ": Command not found\n", 21);
	ft_split_free(string);
	exit(127);
}
