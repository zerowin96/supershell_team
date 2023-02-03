/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:19:11 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 20:01:01 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	main_init_env(t_copy *env, char **envp, char **argv, int argc)
{
	int	i;

	if (argv)
		argc = 0;
	env->cp_envp = 0;
	env->onlyenv = 0;
	i = 0;
	while (envp[i])
	{
		env->onlyenv = vector_add(env->onlyenv, envp[i]);
		env->cp_envp = vector_add(env->cp_envp, envp[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list;
	t_copy	env;
	char	*line;
	int		result;

	result = 0;
	line = 0;
	list = NULL;
	main_init_env(&env, envp, argv, argc);
	while (1)
	{
		if (main_while_init(&list, &line, &result, &env))
			continue ;
		if (pipe_exists(list->next) == 0 && \
		builtin_check(list->next->content))
			main_builtin(list, &result, &env);
		else
		{
			handle_signal();
			result = command_run(list->next, &env);
		}
		delete_local_file(list->next);
		free(line);
		free_list(list);
	}
}