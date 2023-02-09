/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:19:11 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 21:49:36 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	print_art(void)
{
	char	buf[2];
	int		fd;
	int		r;
	int		i;

	i = 1;
	fd = open("/Users/yeham/Desktop/art.txt", O_RDONLY);
	if (fd < 0)
		return ;
	else
	{
		r = read(fd, buf, 1);
		while (r > 0)
		{
			buf[1] = '\0';
			printf("\033[0;3%dm%s\033[0m", i, buf);
			r = read(fd, buf, 1);
			i++;
			if (i == 7)
				i = 1;
		}
	}
	printf("\n");
}

void	main_init_env(t_copy *env, char **envp, char **argv, int argc)
{
	int	index;

	print_art();
	if (!argv)
		argc = 0;
	env->cp_envp = 0;
	env->onlyenv = 0;
	index = 0;
	while (envp[index])
	{
		env->onlyenv = vector_add(env->onlyenv, envp[index]);
		env->cp_envp = vector_add(env->cp_envp, envp[index]);
		index++;
	}
}

int	main_single_builtin_check(t_list **list, int *result, t_copy *env)
{
	if (pipe_exists((*list)->next))
		return (0);
	else
		if (main_builtin(list, result, env))
			return (1);
	return (0);
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
		if (main_while_init(&list, &line, &result))
		{
			free(line);
			continue ;
		}
		if (!(main_single_builtin_check(&list, &result, &env)))
			result = command_run(list->next, &env, result);
		delete_local_file(list->next);
		free(line);
		free_list(list);
	}
}
