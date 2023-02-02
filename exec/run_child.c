/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:54:33 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 20:23:14 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

void	child_process_fd_pre(int (*fd)[2])
{
	if (fd[PREV][READ])
	{
		dup2(fd[PREV][READ], 0);
		close(fd[PREV][READ]);
	}
	if (fd[NEXT][WRITE])
	{
		dup2(fd[NEXT][WRITE], 1);
		close(fd[NEXT][WRITE]);
	}
	if (fd[NEXT][READ])
		close(fd[NEXT][READ]);
}

void	child_process_run(char **command, char **envp)
{
	int		path_index;
	char	**paths;
	int		errcheck;

	path_index = 0;
	errcheck = 0;
	paths = get_path_split(envp);
	path_index = check_access(command[0], paths, X_OK);
	quote_out_command_unhead(&command);
	if (path_index == 1)
		errcheck = execve(command[0], command, envp);
	else if (path_index > 1)
		errcheck = execve(ft_strjoin(paths[path_index - 2], \
		ft_strjoin("/", command[0])), command, envp);
	if (errcheck < 0)
	{
		perror("error on execve");
		exit (1);
	}
	perror("command not found");
	vector_free(command);
	exit(127);
}

void	child_process(t_list *list, t_copy *e, int fd[2][2])
{
	char	**command;
	char	*temp_string;
	int		tnum;
	int		result;

	command = 0;
	temp_string = 0;
	tnum = command_split(list, fd, &command, &temp_string);
	if (tnum)
		exit (tnum);
	child_process_fd_pre(fd);
	if (builtin_check(command[0]))
	{
		result = builtin_exec(temp_string, command, list, e);
		free(temp_string);
		exit (result);
	}
	free(temp_string);
	free_space(list);
	child_process_run(command, e->cp_envp);
	exit (127);
}
