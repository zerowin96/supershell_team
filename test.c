/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:19:11 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 18:19:39 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list->next;
		if (list->content)
		{
			free(list->content);
			list->content = 0;
		}
		free(list);
		list = temp;
	}
}

int	sep_kind(t_list *node)
{
	if (ft_strncmp(node->content, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(node->content, "<<", 3) == 0)
		return (2);
	else if (ft_strncmp(node->content, ">", 2) == 0)
		return (3);
	else if (ft_strncmp(node->content, ">>", 3) == 0)
		return (4);
	else if (ft_strncmp(node->content, "|", 2) == 0)
		return (5);
	return (0);
}

int	pipe_exists(t_list *line)
{
	t_list	*temp;

	temp = line;
	while (temp)
	{
		if (ft_strncmp(((char *)temp->content), "|", 2) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	builtin_check(char *line, t_list *node, t_copy *e, char *string)
{
	int	index;

	index = 0;
	if (ft_strncmp(string, "echo\0", 5) == 0)
		index = 1;
	else if (ft_strncmp(string, "cd\0", 3) == 0)
		index = 2;
	else if (ft_strncmp(string, "pwd\0", 4) == 0)
		index = 3;
	else if (ft_strncmp(string, "export\0", 7) == 0)
		index = 4;
	else if (ft_strncmp(string, "unset\0", 6) == 0)
		index = 5;
	else if (ft_strncmp(string, "env\0", 4) == 0)
		index = 6;
	else if (ft_strncmp(string, "exit\0", 5) == 0)
		index = 7;
	return (index);
}

void	quote_out_command_one(char ***command)
{
	char	*temp_string;

	if ((**command)[0] == (**command)[ft_strlen((**command)) - 1] \
	&& ((**command)[0] == '\'' || (**command)[0] == '\"'))
	{
		temp_string = ft_strdup(&(**command)[1]);
		temp_string[ft_strlen(temp_string) - 1] = 0;
	}
	else
		temp_string = ft_strdup((**command));
	free(**command);
	**command = temp_string;
}

void	quote_out_command_unhead(char ***command)
{
	int		index;
	char	*temp_string;

	index = 1;
	if ((*command)[0] == 0)
		return ;
	while ((*command)[index])
	{
		if ((*command)[index][0] == \
		(*command)[index][ft_strlen(((*command)[index])) - 1] \
		&& ((*command)[index][0] == '\'' || (*command)[index][0] == '\"'))
		{
			temp_string = ft_strdup(&((*command)[index][1]));
			temp_string[ft_strlen(temp_string) - 1] = 0;
		}
		else
		{
			temp_string = ft_strdup((*command)[index]);
		}
		free ((*command)[index]);
		(*command)[index] = temp_string;
		index++;
	}
}

int	quote_check(t_list *list)
{
	int	len;

	while (list->next)
		list = list->next;
	len = ft_strlen((char *)(list->content));
	if (((char *)(list->content))[0] == '\'')
	{
		if (((char *)(list->content))[len - 1] != '\'' || len == 1)
			printf("minishell: quote not closed: close quote\n");
		else
			return (0);
	}
	else if (((char *)(list->content))[0] == '\"')
	{
		if (((char *)(list->content))[len - 1] != '\"' || len == 1)
			printf("minishell: quote not closed: close quote\n");
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

void	main_init_env(t_copy *env, char **envp)
{
	int	i;

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

int main(int argc, char **argv, char **envp)
{
	t_list	*list;
	t_copy	env;
	char	*line;
	int		result;

	result = 0;
	line = 0;
	list = NULL;
	main_init_env(&env, envp);
	while (1)
	{
		if (main_while_init(&list, &line, &result, &env))
			continue ;
		if (pipe_exists(list->next) == 0 && \
		builtin_check(line, list->next, &env, list->next->content))
			main_builtin(list, line, &result, &env);
		else
		{
			handle_signal();
			result = command_run(list->next, line, &env);
		}
		delete_local_file(list->next);
		free(line);
		free_list(list);
	}
}

// cat < infile | awk "{count++} END {print count}"

// ls -al | > a.txt

// export a="ls -la"
// $a
