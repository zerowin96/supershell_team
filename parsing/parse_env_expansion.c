/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:32:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/08 21:44:04 by minsulee         ###   ########.fr       */
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

void	env_expansion_env_string(char *string, \
		char ***vector, int *index, int *start)
{
	int temp_char;

	if ((*index) && ((*index) != (*start)))
	{
		string[(*index)] = 0;
		(*vector) = vector_add((*vector), &(string[(*start)]));
		string[(*index)] = '$';
	}
	(*start) = (*index)++;
	while (ft_isalnum(string[(*index)]) || string[(*index)] == '_')
		(*index)++;
	temp_char = string[(*index)];
	string[(*index)] = 0;
	(*vector) = vector_add((*vector), &(string[(*start)]));
	string[(*index)] = temp_char;
	(*start) = (*index);
}

char	**env_expansion_string_vector(char *string)
{
	int index;
	char **vector;
	int start;
	int temp_char;

	vector = 0;
	index = 0;
	start = 0;
	while (string[index])
	{
		if (string[index] == '$' && 
		(ft_isalpha(string[index + 1]) || string[index + 1] == '_'))
		{
			// if (index && (index != start))
			// {
			// 	string[index] = 0;
			// 	vector = vector_add(vector, &(string[start]));
			// 	string[index] = '$';
			// }
			// start = index++;
			// while (ft_isalnum(string[index]) || string[index] == '_')
			// 	index++;
			// temp_char = string[index];
			// string[index] = 0;
			// vector = vector_add(vector, &(string[start]));
			// string[index] = temp_char;
			// start = index;
		}
		else
			index++;
	}
	if (index != start)
		vector = vector_add(vector, &(string[start]));
	return (vector);
}










void	env_expansion_string(t_list **cursor, char **envp)
{
	int	index;
	int	start;
	int	finish;
	char **vector;
	char *string = (*cursor)->content;
	int temp_char;

	string = (*cursor)->content;
	vector = 0;
	if (string[0] == '\'')
	{
		(*cursor) = (*cursor)->next;
		return ;
	}
	start = 0;
	index = 0;
	// while (string[index])
	// {
	// 	if (string[index] == '$' && 
	// 	(ft_isalpha(string[index + 1]) || string[index + 1] == '_'))
	// 	{
	// 		if (index && (index != start))
	// 		{
	// 			string[index] = 0;
	// 			vector = vector_add(vector, &(string[start]));
	// 			string[index] = '$';
	// 		}
	// 		start = index++;
	// 		while (ft_isalnum(string[index]) || string[index] == '_')
	// 			index++;
	// 		finish = index - 1;
	// 		temp_char = string[index];
	// 		string[index] = 0;
	// 		vector = vector_add(vector, &(string[start]));
	// 		string[index] = temp_char;
	// 		start = index;
	// 	}
	// 	else
	// 		index++;
	// }
	// if (index != start)
	// 	vector = vector_add(vector, &(string[start]));






	t_list *temp_expand;
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
	list_tie(temp_expand);


	t_list *new = temp_expand;
	if (new == 0)
	{
		free(temp_expand->content);
		free(temp_expand);
		free((*cursor)->content);
		(*cursor)->content = ft_strdup("");
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
	free((*cursor)->content);
	(*cursor)->content = new->content;
	(*cursor)->next = new->next;
	(*cursor) = old_last;
	int temp_number = 0;
	free(new);
}







void	env_expansion(t_list *list, char **envp)
{
	t_list	*cursor;

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
	}
}
