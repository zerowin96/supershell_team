/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:56:08 by yeham             #+#    #+#             */
/*   Updated: 2023/02/09 13:58:27 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <stdlib.h>

void	replace_cp_env_key(t_copy *env, char *string, int j)
{
	int	i;

	i = 0;
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], string, j) == 0)
		{
			vector_replace(env->cp_envp, i, string);
			return ;
		}
		i++;
	}
	env->cp_envp = vector_add(env->cp_envp, string);
}

void	replace_onlyenv_key(t_copy *env, char *string, int j)
{
	int	i;

	i = 0;
	while (env->onlyenv[i])
	{
		if (ft_strncmp(env->onlyenv[i], string, j) == 0)
		{
			vector_replace(env->onlyenv, i, string);
			return ;
		}
		i++;
	}
	env->onlyenv = vector_add(env->onlyenv, string);
}

void	same_check(t_copy *env, char *string)
{
	int	i;

	i = 0;
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], string, ft_strlen(string)) == 0)
			return ;
		i++;
	}
	env->cp_envp = vector_add(env->cp_envp, string);
}

void	find_equals_sign(char *string, t_copy *env)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (string[j])
	{
		if (string[j] == '=')
		{
			flag = 1;
			replace_cp_env_key(env, string, j);
			replace_onlyenv_key(env, string, j);
			break ;
		}
		j++;
	}
	if (flag == 0)
		same_check(env, string);
}

int	ft_export(char **command, t_copy *env)
{
	int		result;
	t_list	*temp;
	t_list	*head;

	result = 0;
	head = ft_lstnew(0);
	blank_list_module(command, head);
	temp = head;
	head = head->next;
	if (head->next == NULL)
		sort_and_print(env->cp_envp);
	while (head->next)
	{
		if (export_error_check(head->next->content))
		{
			write(2, "not a valid identifier\n", 23);
			head = head->next;
			result = 1;
			continue ;
		}
		find_equals_sign(head->next->content, env);
		head = head->next;
	}
	free_list(temp);
	return (result);
}
