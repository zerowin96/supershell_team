/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:27:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/06 10:58:25 by minsulee         ###   ########.fr       */
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

	// I MEAN, LET'S DELETE THIS PART
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
	// char	*temp;

	list = ft_lstnew(0);
	tokenize(list, *line);
	// free(*line);
	if (quote_check(list))
	{
		free_list(list);
		return (0);
	}
	// qmark_expansion(list, prev_result);
	// env_expansion(list, envp);


	// temp = listjoin(list);
	// free_list(list);
	// list = ft_lstnew(0);
	// tokenize(list, temp);
	// *line = temp;

	// quote_trim(list);
	// t_list	*print_temp;
	// print_temp = list->next;
	// printf("__________list_print\n");
	// while (print_temp)
	// {
	// 	printf("%s$\n", print_temp->content);
	// 	print_temp = print_temp->next;
	// }









		// tie_temp = tie_temp->next;
	// }

	// printf("__________tie_print\n");
	// print_temp = list->next;
	// // printf("__________list_print\n");
	// while (print_temp)
	// {
	// 	printf("%s$\n", print_temp->content);
	// 	print_temp = print_temp->next;
	// }











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


// t_list *vector_to_list(char ***vector)
// {
// 	t_list	*list;

// 	list = ft_lstnew(0);
// 	if (!vector || !(*vector))
// 		return (0);

// 	int index = 0;
// 	while ((*vector)[index])
// 	{
// 		ft_lstadd_back(&list, ft_lstnew((*vector)[index]));
// 		index++;
// 	}
// 	t_list *temp;
// 	temp = list;
// 	// if (list->next)
// 	// 	temp = list->next;
// 	// free(list);
// 	return (temp);
// }

// char	**list_to_vector(t_list *list)
// {
// 	char **vector;

// 	vector = 0;
// 	list = list->next;
// 	while (list)
// 	{
// 		vector = vector_add(vector, list->content);
// 		list = list->next;
// 	}
// 	return (vector);
// }

// int		ml_iswhite(char c)
// {
// 	if (c == ' ')
// 		return (1);
// 	else if (c >= 9 && c <= 13)
// 		return (1);
// 	return (0);
// }

// char	**whitespace_split(char *string)
// {
// 	int	start;
// 	int	finish;
// 	int	index;
// 	char	**split;

// 	split = 0;
// 	index = 0;
// 	if (string == 0)
// 		return (0);
// 	while (string[index])
// 	{
// 		while (ml_iswhite(string[index]))
// 			index++;
// 		start = index;
// 		while (!(ml_iswhite(string[index])) && string[index])
// 			index++;
// 		finish = index;
// 		string[index] = 0;
// 		split = vector_add(split, &(string[start]));
// 	}
// 	return (split);
// }

// void	list_whitespace_split(t_list *list)
// {
// 	t_list	*prev = list;
// 	list = list->next;
// 	int start;
// 	int finish;
// 	t_list *temp[2];
// 	char	**vector;


// 	while (list)
// 	{
// 		if (((char *)(list->content))[0] == '\'' \
// 		|| ((char *)(list->content))[0] == '\"')
// 			continue;
// 		else
// 		{
// 			int index = 0;
// 			while (((char *)(list->content)))
// 			{
// 				vector = whitespace_split(list->content);
// 				// vector = list_to_vector(list);
// 				temp[0] = vector_to_list(&vector);
// 				temp[1] = list->next;
// 				free(list->content);
// 				free(list);
// 				prev->next = temp[0];
// 				while (temp[0])
// 					temp[0] = temp[0]->next;
// 				temp[0]->next = temp[1];
// 				vector_free(vector);
// 			}
// 		}
// 		prev = list;
// 		list = list->next;
// 	}
// }