/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:59:59 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 14:04:59 by minsulee         ###   ########.fr       */
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

void	parse_expand(char ***command, int result, t_copy *env)
{
	t_list	*temp_list;

	temp_list = vector_to_list(command);
	free(*command);
	list_print("   1", temp_list);
	ft_lstadd_front(&temp_list, ft_lstnew(0));
	qmark_expansion(temp_list, result);
	list_print("   2", temp_list);
	env_expansion(temp_list, env->cp_envp);
	list_print("   3", temp_list);
	quote_trim(temp_list);
	list_print("   4", temp_list);
	free_empty(temp_list);
	list_print("   5", temp_list);
	list_tie(temp_list);
	list_print("   6", temp_list);
	free_space(temp_list);
	list_print("   7", temp_list);
	free_empty(temp_list);
	list_print("   8", temp_list);
	(*command) = list_to_vector(temp_list);
	free_list(temp_list);
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
	parse_expand(&command, *result, env);
	if (!((*list)->next) || !command || !(builtin_check(command[0])))
	{
		free(temp_string);
		vector_free(command);
		return (0);
	}
	main_builtin_fd_mid(fd);
	(*result) = builtin_exec(command, env);
	free(temp_string);
	main_builtin_fd_post(fd);
	return (1);
}
