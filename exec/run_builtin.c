/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:02:10 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/03 11:58:19 by yeham            ###   ########.fr       */
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
	if (command[1])
	{
		if (command[2] != 0)
		{
			ft_putstr_fd("too many arguments\n", 2);
			return (1);
		}
		else
			ft_exit(ft_atoi(command[1]));
	}
	else
		ft_exit(0);
	return (0);
}

int	builtin_exec(char *line, char **command, t_list *node, t_copy *e)
{
	int		index;

	index = builtin_check(command[0]);
	free_space(node);
	if (index == 1)
		ft_echo(line, e);
	else if (index == 2)
		return (builtin_exec_cd(node, e, command));
	else if (index == 3)
		ft_pwd();
	else if (index == 4)
		return (ft_export(line, e));
	else if (index == 5)
		ft_unset(line, e);
	else if (index == 6)
		ft_env(e);
	else if (index == 7)
		return (builtin_exec_exit(command));
	return (0);
}
