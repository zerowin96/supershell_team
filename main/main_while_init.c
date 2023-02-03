/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_while_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:09:01 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/03 13:41:44 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	command_check(t_list *list)
{
	int	index;

	index = 0;
	list = list->next;
	while (list)
	{
		if (sep_kind(list) && (!(list->next) || ((((char *) \
		(list->next->content))[0] == ' ') && !(list->next->next))))
			index = printf("syntax error near unexpected token `newline'\n");
		else if (sep_kind(list) && (((char *)(list->next->content \
		))[0] == ' ') && sep_kind(list->next->next))
			index = printf("syntax error near unexpected token '%s'\n", \
			(char *)(list->next->next->content));
		else if (sep_kind(list) && sep_kind(list->next))
			index = printf("syntax error near unexpected token '%s'\n", \
			(char *)(list->next->content));
		if (index)
			return (258);
		if (sep_kind(list) == 0)
			list = list->next;
		else
			list = list->next->next;
	}
	return (0);
}

char	*reading(void)
{
	char	*line;

	line = readline("minishell 1.0$ ");
	if (line == 0)
	{
		rl_replace_line("", 1);
		write(2, "exit\n", 5);
		exit (0);
	}
	if (line && *line)
		add_history(line);
	else
		free(line);
	return (line);
}

int	main_while_init(t_list **list, char **line, int *result, t_copy *env)
{
	handle_signal();
	(*line) = reading();
	if ((*line) == 0 || (**line) == 0)
		return (1);
	(*list) = first_parsing(line, env->cp_envp, (*result));
	if ((*list) == 0)
		return (1);
	if (command_check((*list)))
		(*result) = 258;
	else if (heredoc((*list)->next))
		(*result) = 130;
	else
		return (0);
	free((*line));
	free_list((*list));
	return (1);
}