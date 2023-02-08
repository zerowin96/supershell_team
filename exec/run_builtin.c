/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:02:10 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/08 22:13:27 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	builtin_exec_cd(t_list *node, t_copy *e, char **command)
{
	if (command[1])
	{
		if (command[2] != 0)
		{
			ft_putstr_fd("too many arguments\n", 2);
			return (1);
		}
		else
			return (ft_cd((char *)node->next->content, e));
	}
	else
		return (ft_cd(NULL, e));
}

int	builtin_exec_exit(char **command)
{
	int	i;

	i = 0;
	if (command[1])
		ft_exit(command[1], command[2]);
	else
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	return (0);
}

int	builtin_exec(char *line, char **command, t_list *node, t_copy *e)
{
	int		index;

	index = builtin_check(command[0]);
	// t_list *temp = vector_to_list(&command);
	// while(temp)
	// {
	// 	printf("command == %s\n", (char *)temp->content);
	// 	temp = temp->next;
	// }

	int index1 = 0;
	char *temp_line = 0;\
	char *temp_line2;
	while (command[index1])
	{
		temp_line2 = ft_strjoin(temp_line, command[index1]);
		free(temp_line);
		index1++;
		if (command[index1])
		{
			temp_line = ft_strjoin(temp_line2, " ");
			free(temp_line2);
		}	
	}
	temp_line = temp_line2;

	if (index == 1)
		ft_echo(temp_line, e);
	else if (index == 2)
		return (builtin_exec_cd(node, e, command));
	else if (index == 3)
		ft_pwd();
	else if (index == 4)
		return (ft_export(temp_line, e));
	else if (index == 5)
		ft_unset(temp_line, e);
	else if (index == 6)
		ft_env(e);
	else if (index == 7)
		return (builtin_exec_exit(command));
	free(temp_line);
	return (0);
}
