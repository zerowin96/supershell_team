/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:17:01 by yeham             #+#    #+#             */
/*   Updated: 2023/01/10 22:12:53 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// void ft_echo()
// {
	
// }

// void ft_cd()
// {
	
// }

// void ft_pwd()
// {
	
// }

// void ft_export()
// {
	
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
	printf("%s", *env->cp_envp);
	int i;

	i = 0;

	printf("env temp ==> ");
	
	while (env->cp_envp[i])
	{
		printf("%s\n", env->cp_envp[i]);
		i++;
	}
}

// void ft_env()
// {
	
// }

// void ft_exit()
// {
	
// }
