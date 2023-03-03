/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:17:01 by yeham             #+#    #+#             */
/*   Updated: 2023/01/30 21:29:14 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_env(t_copy *env)
{
	int	i;

	i = 0;
	while (env->onlyenv[i])
	{
		printf("%s\n", env->onlyenv[i]);
		i++;
	}
	return ;
}

void	blank_list_module(char **string, t_copy *env, t_list *new)
{
	char	*temp;
	int		i;

	i = 0;
	while (string[i])
	{
		temp = disassemble_assemble(string[i], env->cp_envp);
		ft_lstadd_back(&new, ft_lstnew(temp));
		i++;
	}
}