/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:27:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/03 21:43:23 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_list	*parsing(char *line, char **envp)
{
	t_list	*list;

	list = ft_lstnew(0);
	tokenize(list, line);
	if (quote_check(list))
		return (0);

	int index;
	if (envp)
		index = 1;
	else if (envp == 0)
		index = 2;
	else
		env_expansion(list, envp);

	return (list);
}

char	*listjoin(t_list *list)
{
	t_list	*cursor;
	char	*temp;
	char	*temp1;

	temp = 0;
	temp1 = 0;
	cursor = list->next;
	temp1 = (char *)ft_calloc(1, sizeof(char));
	while (cursor)
	{
		temp = ft_strjoin(temp1, cursor->content);
		free(temp1);
		temp1 = temp;
		cursor = cursor->next;
	}
	return (temp);
}

t_list	*first_parsing(char **line, char **envp, int prev_result)
{
	t_list	*list;
	char	*temp;

	list = ft_lstnew(0);
	tokenize(list, *line);
	free(*line);
	if (quote_check(list))
	{
		free_list(list);
		return (0);
	}
	qmark_expansion(list, prev_result);
	env_expansion(list, envp);


	temp = listjoin(list);
	free_list(list);
	list = ft_lstnew(0);
	tokenize(list, temp);
	*line = temp;

	quote_trim(list);
	t_list	*print_temp;
	print_temp = list->next;
	printf("__________list_print\n");
	while (print_temp)
	{
		printf("%s$\n", print_temp->content);
		print_temp = print_temp->next;
	}



	t_list	*tie_temp;
	t_list	*tie_prev;
	tie_temp = list->next->next;
	tie_prev = list->next;
	while(tie_temp)
	{
		if (((char *)(tie_temp->content))[0] == 0)
		{
			tie_prev->next = tie_temp->next;
			free(tie_temp->content);
			free(tie_temp);
			tie_temp = tie_prev->next;
		}
		else if (((char *)(tie_prev->content))[0] != ' ' && (((char *)(tie_temp->content))[0] != ' '))
		{
			char	*temp_string;
			temp_string = ft_strjoin(tie_prev->content, tie_temp->content);
			free (tie_prev->content);
			tie_prev->content = temp_string;
			tie_prev->next = tie_temp->next;
			free(tie_temp->content);
			free(tie_temp);
			tie_temp = tie_prev->next;
		}
		else
		{
			tie_prev = tie_temp;
			tie_temp = tie_prev->next;
		}





		// tie_temp = tie_temp->next;
	}

	printf("__________tie_print\n");
	print_temp = list->next;
	// printf("__________list_print\n");
	while (print_temp)
	{
		printf("%s$\n", print_temp->content);
		print_temp = print_temp->next;
	}











	return (list);
}

// t_list	*print_temp;
// print_temp = list->next;
// printf("__________list_print\n");
// while (print_temp)
// {
// 	printf("%s$\n", print_temp->content);
// 	print_temp = print_temp->next;
// }