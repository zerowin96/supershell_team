/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:32:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/07 17:29:30 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*env_expansion_string_a_env(char **envp, char *temp)
{
	char	*temp2;
	int		index;

	temp2 = 0;
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], temp, ft_strlen(temp)) == 0)
		{
			temp2 = &(envp[index][ft_strlen(temp)]);
			break ;
		}
		index++;
	}
	return (temp2);
}

void	env_expansion_string_a(char **string, char **envp, int *index)
{
	int		start;
	int		finish;
	char	*temp[3];

	start = ++(*index);
	while (ft_isalnum((*string)[(*index)]) || (*string)[*index] == '_')
		(*index)++;
	finish = (*index) - 1;
	temp[0] = (char *)ft_calloc(finish - start + 3, sizeof(char));
	ft_memmove(temp[0], &(*string)[start], finish - start + 1);
	temp[0][finish - start + 1] = '=';
	temp[1] = env_expansion_string_a_env(envp, temp[0]);
	free(temp[0]);
	temp[2] = ft_strjoin2(temp[1], *string, start, finish);
	free(*string);
	*string = temp[2];
	(*index) = (start - 1) + ft_strlen(temp[1]);
}

// void	env_expansion_string(char **string, char **envp)
// {
// 	int	index;

// 	index = 0;
// 	if ((*string)[index] == '\'')
// 		return ;
// 	while ((*string)[index])
// 	{
// 		if ((*string)[index] == '$' && (*string)[index + 1])
// 			env_expansion_string_a(string, envp, &index);
// 		else
// 			index++;
// 	}
// }

void	env_expansion_string(t_list **list, char **envp)
{
	int		index;
	char	**string;

	// char	**vector = 0;

	string = (char **)(&((*list)->content));
	index = 0;
	if ((*string)[index] == '\'')
		return ;
	while ((*string)[index])
	{
		if ((*string)[index] == '$' && 
		(ft_isalnum((*string)[index + 1]) || (*string)[index + 1] == '_')
		&& !ft_isdigit((*string)[index + 1]))
		{
			env_expansion_string_a(string, envp, &index);
			// printf("env_expansion_string : %s$\n", (*string));
		}
		else
			index++;
	}

	t_list	*new = ft_lstnew(0);
	tokenize_2(new, *string);
	printf("STRING : %s$\n", *string);
	list_print("STRING : ", new);
	// if (!(new->next))
	// 	ft_lstadd_back(&new, ft_lstnew(" "));
	// list_print("tokenized", new);

	if (new->next == 0)
	{
		free(new->content);
		new->content = 0;
		free(new);
		new = 0;
		return ;
	}






	t_list	*new_last;
	new_last = new;
	while (new_last->next)
		new_last = new_last->next;


	t_list *old_next;
	old_next = (*list)->next;


	new_last->next = old_next;

	if (new->next)
	{
		free((*list)->content);
		(*list)->content = new->next->content;
		(*list)->next = new->next->next;
	}

	(*list) = new_last;
	new->next = 0;
	free(new->content);
	new->content = 0;
	free(new);
	new = 0;
	return ;
	// list_print("tokenized__POST", new);


}

void	env_expansion(t_list *list, char **envp)
{
	t_list	*cursor;
	list_print("env_expansion_PREV", list);
	cursor = list->next;
	while (cursor)
	{
		
		if (!(cursor->content))
		{
			cursor = cursor->next;
			continue;
		}
		if (ft_strncmp(cursor->content, " ", 2) == 0)
		{
			cursor = cursor->next;
			continue;
		}
		env_expansion_string(&cursor, envp);
		if (cursor)
			cursor = cursor->next;
	}
	list_print("env_expansion_POST", list);
}
