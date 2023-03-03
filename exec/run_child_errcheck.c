/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_errcheck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:03:10 by yeham             #+#    #+#             */
/*   Updated: 2023/02/08 23:05:50 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	not_directory_check(char *command, int errcheck)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
		{
			perror("");
			exit(127);
		}
		i++;
	}
	if (errcheck < 0)
	{
		perror("");
		exit(1);
	}
	write(2, "command not found\n", 19);
}

void	child_command_error(char *command, int errcheck)
{
	struct stat	file_status;

	stat(command, &file_status);
	if (S_ISDIR(file_status.st_mode))
	{
		printf("Is a directory\n");
		exit(126);
	}
	else
		not_directory_check(command, errcheck);
}
