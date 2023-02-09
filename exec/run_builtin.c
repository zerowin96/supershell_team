/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:02:10 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 13:57:54 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	builtin_exec_cd(char **command, t_copy *e)
{
	if (command[1])
	{
		if (command[2] != 0)
		{
			ft_putstr_fd("too many arguments\n", 2);
			return (1);
		}
		else
		{
			return (ft_cd(command[1], e));
		}
	}
	else
	{
		return (ft_cd(NULL, e));
	}
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

char	*make_line(char **command)
{
	int		i;
	char	*temp_line;
	char	*temp_line2;

	i = 0;
	temp_line = 0;
	temp_line2 = 0;
	while (command[i])
	{
		temp_line2 = ft_strjoin(temp_line, command[i]);
		free(temp_line);
		i++;
		if (command[i])
		{
			temp_line = ft_strjoin(temp_line2, " ");
			free(temp_line2);
		}
	}
	temp_line = temp_line2;
	return (temp_line);
}

int	builtin_exec(char **command, t_copy *e)
{
	int		index;
	int		result;

	index = builtin_check(command[0]);
	result = 0;
	if (index == 1)
		ft_echo(command);
	else if (index == 2)
		result = builtin_exec_cd(command, e);
	else if (index == 3)
		ft_pwd();
	else if (index == 4)
		result = ft_export(command, e);
	else if (index == 5)
		ft_unset(command, e);
	else if (index == 6)
		ft_env(e);
	else if (index == 7)
		result = builtin_exec_exit(command);
	vector_free(command);
	return (result);
}
