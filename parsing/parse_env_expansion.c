/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:32:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/08 15:57:00 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*env_expansion_string_a_env(char **envp, char *temp)
{
	char	*temp2;
	int		index;
	char	*key;

	index = ft_strlen(temp);
	key = (char *)ft_calloc((index),  sizeof(char));
	ft_memmove(key, &temp[1], index - 1);
	key[index - 1] = '=';
	// printf("key : %s||\n", key);

	temp2 = 0;
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], key, ft_strlen(key)) == 0)
		{
			temp2 = &(envp[index][ft_strlen(key)]);
			break ;
		}
		index++;
	}
	free(key);
	return (temp2);
}

// void	env_expansion_string_a(char **string, char **envp, int *index)
// {
// 	int		start;
// 	int		finish;
// 	char	*temp[3];

// 	start = ++(*index);
// 	while (ft_isalnum((*string)[(*index)]) || (*string)[*index] == '_')
// 		(*index)++;
// 	finish = (*index) - 1;
// 	temp[0] = (char *)ft_calloc(finish - start + 3, sizeof(char));
// 	ft_memmove(temp[0], &(*string)[start], finish - start + 1);
// 	temp[0][finish - start + 1] = '=';
// 	temp[1] = env_expansion_string_a_env(envp, temp[0]);
// 	free(temp[0]);
// 	temp[2] = ft_strjoin2(temp[1], *string, start, finish);
// 	free(*string);
// 	*string = temp[2];
// 	(*index) = (start - 1) + ft_strlen(temp[1]);
// }

// void	env_expansion_string_a(t_list *list, char *string, char **envp, int *index)
// {
// 	int		start;
// 	int		finish;
// 	char	*temp[3];

// 	start = ++(*index);
// 	while (ft_isalnum(string[*index]) || string[*index] == '_')
// 		(*index)++;
// 	finish = (*index) - 1;
// 	temp[0] = (char *)ft_calloc(finish - start + 3, sizeof(char));
// 	ft_memmove(temp[0], &string[start], finish - start + 1);
// 	temp[0][finish - start + 1] = '='; // : "PATH="-like-string.
// 	temp[1] = env_expansion_string_a_env(envp, temp[0]); // : EXPANSION STRING
// 	free(temp[0]);
// 	temp[0] = 0;
	


// 	t_list *new_temp;
// 	new_temp = ft_lstnew(0);
// 	if (temp[1] && temp[1][0])
// 	{
// 		tokenize_2(new_temp, temp[1]); //new temp에 parse해서 붙이기
// 		if (new_temp->next)
// 		{
// 			t_list *last = new_temp;;
// 			while (last->next)
// 				last = last->next;
// 			last->next = list->next;
			
			
// 		}
// 	}
// 	else
// 	{
		
// 	}
// 	list_print("env expanding with tokenizing", list);
// 	// ft_lstadd_back(&list, ft_lstnew(ft_strdup(temp[1])));
	


// 	// temp[2] = ft_strjoin2(temp[1], *string, start, finish);
// 	// free(*string);
// 	// *string = temp[2];
// 	// (*index) = (start - 1) + ft_strlen(temp[1]);
// }

// // void	env_expansion_string(char **string, char **envp)
// // {
// // 	int	index;

// // 	index = 0;
// // 	if ((*string)[index] == '\'')
// // 		return ;
// // 	while ((*string)[index])
// // 	{
// // 		if ((*string)[index] == '$' && (*string)[index + 1])
// // 			env_expansion_string_a(string, envp, &index);
// // 		else
// // 			index++;
// // 	}
// // }

// void	env_expansion_string(t_list **list, char **envp)
// {
// 	int		index;
// 	char	*string;

// 	// char	**vector = 0;

// 	// string = (char **)(&((*list)->content));
// 	// index = 0;
// 	// if ((*string)[index] == '\'')
// 	// 	return ;
// 	// while ((*string)[index])
// 	// {
// 	// 	if ((*string)[index] == '$' && 
// 	// 	(ft_isalnum((*string)[index + 1]) || (*string)[index + 1] == '_')
// 	// 	&& !ft_isdigit((*string)[index + 1]))
// 	// 	{
// 	// 		env_expansion_string_a(string, envp, &index);
// 	// 		// printf("env_expansion_string : %s$\n", (*string));
// 	// 	}
// 	// 	else
// 	// 		index++;
// 	// }

// 	int start;
// 	int finish;
// 	t_list	*temp;
// 	temp = ft_lstnew(0);

// 	string = (char *)(((*list)->content));
// 	index = 0;
// 	if (string[index] == '\'')
// 		return ;
// 	start = 0;
// 	while (string[index])
// 	{
// 		if (string[index] == '$' && 
// 		(ft_isalnum(string[index + 1]) || string[index + 1] == '_')
// 		&& !ft_isdigit(string[index + 1]))
// 		{
// 			// from start(index 0 or right next to ENV) to "current index - 1" (as index), 
// 			// tie them into list;
// 			if (index)
// 			{
// 				string[index] = 0;
// 				printf("list_new : %s\n", &string[start]);
// 				printf("i am watching : %s\n", &string[index + 1]);
// 			}
// 			ft_lstadd_back(&temp, ft_lstnew(&string[start]));
// 			// string[index] = '$';
// 			env_expansion_string_a(*list, string, envp, &index);
// 			start = index;
// 			// index는 이제 $ENV의 다음 위치를 지목한다.
// 			// start = ++index;
// 			// while (ft_isalnum(string[index]) || string[index] == '_')
// 			// 	index++;
// 			// finish = index - 1;
// 		}
// 		else
// 			index++;
// 	}
// 	// free(string);
	
// 	// 이제 *list -> next 를 저장하고
// 	// *list 의 content temp->next->content 로,
// 	// *list->next 를 temp->next->next 로 바꾼다












// 	// t_list	*new = ft_lstnew(0);
// 	// tokenize_2(new, *string);
// 	// printf("STRING : %s$\n", *string);
// 	printf("%s ", string);
// 	list_print("STRING : ", temp);
// 	t_list *new = temp;
// 	// if (!(new->next))
// 	// 	ft_lstadd_back(&new, ft_lstnew(" "));
// 	// list_print("tokenized", new);

// 	if (new->next == 0)
// 	{
// 		free(new->content);
// 		new->content = 0;
// 		free(new);
// 		new = 0;
// 		return ;
// 	}






// 	t_list	*new_last;
// 	new_last = new;
// 	while (new_last->next)
// 		new_last = new_last->next;


// 	t_list *old_next;
// 	old_next = (*list)->next;


// 	new_last->next = old_next;

// 	if (new->next)
// 	{
// 		free((*list)->content);
// 		(*list)->content = new->next->content;
// 		(*list)->next = new->next->next;
// 	}

// 	(*list) = new_last;
// 	new->next = 0;
// 	free(new->content);
// 	new->content = 0;
// 	free(new);
// 	new = 0;
// 	return ;
// 	// list_print("tokenized__POST", new);
// }

















































void	env_expansion_string(t_list **cursor, char **envp)
{
	int	index;
	int	start;
	int	finish;
	// t_list *temp;
	char **vector = 0;
	// temp = ft_lstnew(0);

	char *string = (*cursor)->content;

	// write(2, " 001 : ", 8);
	// system("leaks a.out | grep total");


	if (string[0] == '\'')
	{
		(*cursor) = (*cursor)->next;
		return ;
	}
	start = 0;
	index = 0;
	while (string[index])
	{
		if (string[index] == '$' && 
		(ft_isalpha(string[index + 1]) || string[index + 1] == '_'))
		{
			if (index && (index != start))
			{
				string[index] = 0;
				vector = vector_add(vector, &(string[start]));
				// printf("%s\n", &(string[start]));
				string[index] = '$';
			}
			start = index++; // now start = &
			while (ft_isalnum(string[index]) || string[index] == '_')
				index++;
			finish = index - 1;

			int temp_char = string[index];
			string[index] = 0;
			// printf("%s\n", &(string[start]));
			vector = vector_add(vector, &(string[start]));
			string[index] = temp_char;
			start = index; // now start = next of $ENV
		}
		else
			index++;
	}
	if (index != start)
		vector = vector_add(vector, &(string[start]));

	// printf("+++++++++++++++++++++++++++\n\n\n\n\n\n\n\n");
	// vector_print("EXPANDING", vector);

	// write(2, " 002 : ", 8);
	// system("leaks a.out | grep total");
	// vector_print("BEFORE EXPANSION", vector);
	t_list *temp_expand;;
	t_list *temp_cursor;
	temp_expand = ft_lstnew(0);
	if (vector)
	{
		index = 0;
		temp_cursor = temp_expand;
		while (vector && vector[index])
		{
			if (vector[index][0] == '$' && vector[index][1] != '$' && vector[index][1])
			{
				char *env = env_expansion_string_a_env(envp, vector[index]);
				if (env)
				{
					vector_replace(vector, index, env);
					tokenize_2(temp_cursor, vector[index++]);
				}
				else
					vector = vector_delete_index(vector, index);
			}
			else
				temp_cursor->next = ft_lstnew(ft_strdup(vector[index++]));
			while (temp_cursor->next)
				temp_cursor = temp_cursor->next;
		}
	}
	vector_free(vector);

	// list_print("TEST0", temp_expand);
	list_tie(temp_expand);
	// list_print("TEST1", temp_expand);

	t_list *new = temp_expand;
	if (new == 0)
	{
		free((*cursor)->content);
		(*cursor)->content = ft_lstnew(0);
		(*cursor) = (*cursor)->next;
		return ;
	}
	t_list *old_last;
	old_last = (*cursor)->next;
	t_list *new_last;
	new_last = new;
	while (new_last->next)
		new_last = new_last->next;
	new_last->next = old_last;
	if (new)
	{
		free((*cursor)->content);
		(*cursor)->content = new->content;
		(*cursor)->next = new->next;
	}
	(*cursor) = old_last;





}







void	env_expansion(t_list *list, char **envp)
{
	t_list	*cursor;
	// list_print("env_expansion_PREV", list);
	cursor = list->next;
	while (cursor)
	{
		
		if (!(cursor->content))
		{
			cursor = cursor->next;
			continue;
		}
		if (!ft_strncmp(cursor->content, " ", 2))
		{
			cursor = cursor->next;
			continue;
		}
		env_expansion_string(&cursor, envp);
		// if (cursor)
		// 	cursor = cursor->next;
	}
	// list_print("env_expansion_POST", list);
	// system("leaks a.out");
	// exit (1);
}
