/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:59:59 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/08 15:57:21 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	main_builtin_init(int (*fd)[2], char ***command, char **temp_string)
{
	*command = 0;
	*temp_string = 0;
	fd[0][0] = 0;
	fd[0][1] = 0;
	fd[1][0] = 0;
	fd[1][1] = 0;
	fd[2][0] = dup(0);
	fd[2][1] = dup(1);
}

void	main_builtin_fd_post(int (*fd)[2])
{
	dup2(fd[2][0], 0);
	dup2(fd[2][1], 1);
	close(fd[2][0]);
	close(fd[2][1]);
}

void	main_builtin_fd_mid(int (*fd)[2])
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
}

int	main_builtin(t_list **list, int *result, t_copy *env)
{
	char	**command;
	char	*temp_string;
	int		fd[3][2];
	int		tnum;

	main_builtin_init(fd, &command, &temp_string);
	tnum = command_split((*list)->next, fd, &command, &temp_string);
	if (tnum)
	{
		(*result) = tnum;
		return (tnum);
	}
	//test

	t_list *temp_list;
	// free_list(temp_list);
	// list_print("single_builtin part", *list);
	// vector_print("single_builtin part", command);
	temp_list = vector_to_list(&command);
	// vector_free(command);
	free(command);
	ft_lstadd_front(&temp_list, ft_lstnew(0));
	// list_whitespace_split(temp_list);
	// list_print("MAIN 0", temp_list);
	qmark_expansion(temp_list, *result);
	// list_print("MAIN 1", temp_list);
	env_expansion(temp_list, env->cp_envp);
	// list_print("MAIN 2", temp_list);
	// list_tie(temp_list);
	quote_trim(temp_list);
	// list_print("MAIN 3", temp_list);
	free_empty(temp_list);
	// list_print("MAIN 4", temp_list);
	// vector_print("AFTER EXPANSION", command);
	// list_print("AFTER SPLIT", temp_list);
	// vector_print("AFTER SPLIT", command);
	list_tie(temp_list);
	// list_print("MAIN 5", temp_list);
	// quote_trim(temp_list);
	free_space(temp_list);
	// free_space(temp_list);
	// list_print("after freeing space", temp_list);
	// list_print("BEFORE_FREE_EMPTY", temp_list);
	free_empty(temp_list);
	// list_print("SINGLE_BUILTIN_RUN", temp_list);
	command = list_to_vector(temp_list);



	// exit (1111111111);

	// free_list((*list));
	// (*list) = vector_to_list(&command);
	// ft_lstadd_front(&(*list), ft_lstnew(0));
	// qmark_expansion((*list), *result);
	// env_expansion((*list), env->cp_envp);
	// list_whitespace_split((*list));
	// quote_trim((*list));
	// list_tie((*list));
	// free_space((*list));
	// free_empty((*list));
	// command = list_to_vector((*list));
	// list_print("single_builtin part list", temp_list);

	
	// vector_print("single_builtin part command", command);
	free_list(temp_list);

	
	if (!((*list)->next) || !(builtin_check((*list)->next->content)))
	{
		if (temp_string)
			free(temp_string);
		if (command)
			vector_free(command);
		return (0);
	}
	//test
	main_builtin_fd_mid(fd);
	(*result) = builtin_exec(temp_string, command, (*list)->next, env);
	if (command)
		vector_free(command);
	if (temp_string)
		free(temp_string);
	main_builtin_fd_post(fd);
	return (1);
}
