/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:17:01 by yeham             #+#    #+#             */
/*   Updated: 2023/01/12 21:26:57 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// void ft_echo()
// {
	//lsof
// }

// void ft_cd()
// {
	
// }

// void ft_pwd()
// {
	
// }
			// while (env->cp_envp[i])
			// {
			// 	if (ft_strncmp(env->cp_envp[i], string, ft_strlen(string)) == 0)
			// 	{
			// 		flag = pass;
			// 		break ;
			// 	}
			// 	i++;
			// }

			// if (flat != 'pass')
			// {
			// 	env->cp_envp[i] = node->next->content;
			// 	env->cp_envp[i + 1] = 0;
			// }


void ft_unset(char *temp, t_copy *env)
{

	int i;

	i = 0;

	printf("unset temp ==> %s\n", temp);

	while (env->cp_envp[i])
	{
		//찾았다면
		if (ft_strncmp(env->cp_envp[i], temp, ft_strlen(temp)) == 0)
		{
			//지우고
			env->cp_envp[i] = NULL;
			//땡겨라
			while (env->cp_envp[i + 1])
			{
				env->cp_envp[i] = env->cp_envp[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}


void ft_env(t_copy *env)
{
	int i;
	int fd = 1;

	i = 0;

	printf("env temp ==> ");
	
	while (env->cp_envp[i])
	{
		write(fd, env->cp_envp[i], ft_strlen(env->cp_envp[i]));
		write(fd, "\n", 1);
		i++;
	}
}


// void ft_exit()
// {
	
// }
