/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:54:33 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/08 22:13:26 by minsulee         ###   ########.fr       */
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
	if (path_index == 1)
		errcheck = execve(command[0], command, envp);
	else if (path_index > 1)
		errcheck = execve(ft_strjoin(paths[path_index - 2], \
		ft_strjoin("/", command[0])), command, envp);
	child_command_error(command[0], errcheck);
	vector_free(command);
	exit(127);
}

void	child_process(t_list **list, t_copy *e, int fd[2][2], int result)
{
	char	**command;
	char	*temp_string;
	int		tnum;

	command = 0;
	temp_string = 0;
	child_handle_signal();
	tnum = command_split(*list, fd, &command, &temp_string);
	if (tnum)
		exit (tnum);
	parse_expand(&command, result, e);
	child_process_fd_pre(fd);
	if (command == 0 || command[0] == 0)
	{
		vector_free(command);
		exit (0);
	}
	if (builtin_check(command[0]))
	{
		result = builtin_exec(temp_string, command, *list, e);
		exit (result);
	}
	child_process_run(command, e->cp_envp);
	exit (127);
}
