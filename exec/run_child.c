/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:54:33 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/07 19:19:09 by minsulee         ###   ########.fr       */
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
	// printf("path index == %d\n", path_index);
	// CHECK IF INPUT IS FOLDER OR NOT
	// CHECK IF 
	// quote_out_command_unhead(&command);
	// printf("%s is running\n", command[0]);
	// vector_print("child process run", command);
	// printf("----------\n");
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
	write(2, "command not found\n", 19);
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd("\n", 2);
	vector_free(command);
	exit(127);
}

void	child_process(t_list **list, t_copy *e, int fd[2][2], int result)
{
	char	**command;
	char	*temp_string;
	int		tnum;
	// int		result;

	t_list	*temp;

	command = 0;
	temp_string = 0;
	child_handle_signal();
	tnum = command_split(*list, fd, &command, &temp_string);
	if (tnum)
		exit (tnum);
	
	// static int index;
	// printf("------child_process_------\n");
	// list_print("list", *list);
	// vector_print("vector", command);


	//test
	t_list	*temp_list;
	// free_list(temp_list);
	temp_list = vector_to_list(&command);
	ft_lstadd_front(&temp_list, ft_lstnew(0));
	// list_print("child 0", temp_list);
	// list_whitespace_split(temp_list);
	// list_print("child 1", temp_list);
	quote_trim(temp_list);
	// list_print("child 2", temp_list);
	qmark_expansion(temp_list, result);
	// list_print("child 3", temp_list);
	env_expansion(temp_list, e->cp_envp);
	// list_print("child 4", temp_list);
	list_tie(temp_list);
	// list_print("child 5", temp_list);
	// list_print("child 3", temp_list);
	// temp = vector_to_list(&command);
	// free_space(temp);
	// free_empty(temp);
	free_space(temp_list);
	// free_space(temp_list);
	free_empty(temp_list);
	// vector_free(command);
	free(command);
	command = list_to_vector(temp_list);
	// command = list_to_vector(*list);
	// printf("child process\n");
	// list_print("child process", temp_list);
	// vector_print("child FIN", command);
	// list_print("child FIN", temp_list);
	// printf("command : &&%s&&\n", command[0]);
	//test
	child_process_fd_pre(fd);
	if (command == 0 || command[0] == 0)
	{
		if (command)
			vector_free(command);
		exit (0);
	}

	if (builtin_check(command[0]))
	{
		result = builtin_exec(temp_string, command, *list, e);
		free(temp_string);
		exit (result);
	}
	free(temp_string);
	free_space(*list);
	// system("leaks a.out");
	child_process_run(command, e->cp_envp);
	exit (127);
}
