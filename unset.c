/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:13:34 by yeham             #+#    #+#             */
/*   Updated: 2023/01/30 21:25:16 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	**only_pick_key(char **key_vector)
{
	int	i;
	int	j;

	i = 0;
	while (key_vector[i])
	{
		j = 0;
		while (key_vector[j])
		{
			if (key_vector[i][j] == '=')
			{
				key_vector[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
	return (key_vector);
}

char	**find_key(char **env)
{
	char	**key_vector;
	int		i;

	key_vector = 0;
	i = 0;
	while (env[i])
	{
		key_vector = vector_add(key_vector, env[i]);
		i++;
	}
	return (only_pick_key(key_vector));
}

void	ft_unset(char *line, t_copy *env)
{
	int i;
	int j;
	char *real_test;
	char **string;
	char **key_env;
	char **key_export;
	t_list *a;
	t_list *test_a;

	a = ft_lstnew(0);
	string = env_split(line);
	blank_list_module(string, env, a);
	test_a = a->next;
	if (test_a->next == NULL)
		return ;
	key_export = 0;
	key_export = find_key(env->cp_envp);
	key_env = find_key(env->onlyenv);

	while (test_a->next)
	{
		i = 0;
		while (env->cp_envp[i])
		{
			if (ft_strcmp(key_export[i], test_a->next->content) == 0)
			{
				while (env->cp_envp[i + 1])
				{
					env->cp_envp[i] = env->cp_envp[i + 1];
					key_export[i] = key_export[i + 1];
					i++;
				}
				env->cp_envp[i] = NULL;
				key_export[i] = NULL;
				break ;
			}
			i++;
		}
		i = 0;
		while (env->onlyenv[i])
		{
			if (ft_strcmp(key_env[i], test_a->next->content) == 0)
			{
				while (env->onlyenv[i + 1])
				{
					env->onlyenv[i] = env->onlyenv[i + 1];
					key_env[i] = key_env[i + 1];
					i++;
				}
				env->onlyenv[i] = NULL;
				key_env[i] = NULL;
				break ;
			}
			i++;
		}
		test_a = test_a->next;
	}
}