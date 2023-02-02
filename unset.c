/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:13:34 by yeham             #+#    #+#             */
/*   Updated: 2023/02/01 20:49:52 by yeham            ###   ########.fr       */
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

void	erase_export(t_copy *env, char ***key_export, char *string)
{
	int	i;

	i = 0;
	while (env->cp_envp[i])
	{
		if (ft_strcmp((*key_export)[i], string) == 0)
		{
			env->cp_envp = vector_delete_index(env->cp_envp, i);
			*key_export = vector_delete_index(*key_export, i);
			break ;
		}
		i++;
	}	
}

void	erase_env(t_copy *env, char ***key_env, char *string)
{
	int	i;

	i = 0;
	while (env->onlyenv[i])
	{
		if (ft_strcmp((*key_env)[i], string) == 0)
		{
			env->onlyenv = vector_delete_index(env->onlyenv, i);
			*key_env = vector_delete_index(*key_env, i);
			break ;
		}
		i++;
	}	
}

void	ft_unset(char *line, t_copy *env)
{
	char	**key_env;
	char	**key_export;
	t_list	*head;
	t_list	*temp;

	head = ft_lstnew(0);
	blank_list_module(env_split(line), env, head);
	temp = head;
	head = head->next;
	if (head->next == NULL)
		return ;
	key_export = 0;
	key_env = 0;
	key_export = find_key(env->cp_envp);
	key_env = find_key(env->onlyenv);
	while (head->next)
	{
		erase_export(env, &key_export, head->next->content);
		erase_env(env, &key_env, head->next->content);
		head = head->next;
	}
	free_list(temp);
	vector_free(key_export);
	vector_free(key_env);
}
