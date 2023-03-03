/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:32:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 19:26:19 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*env_expansion_string_a_env(char **envp, char *temp)
{
	char	*temp2;
	int		index;
	char	*key;

	index = ft_strlen(temp);
	key = (char *)ft_calloc(index + 1, sizeof(char));
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

void	env_expansion_envstring(char *string, \
		char ***vector, int *index, int *start)
{
	int	temp_char;

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

void	env_expansion_v2elst_str(t_list *temp_cursor, \
		char ***vector, int *index, char **envp)
{
	char	*env;

	if ((*vector)[(*index)][0] == '$' && \
	(*vector)[(*index)][1] != '$' && (*vector)[(*index)][1])
	{
		env = env_expansion_string_a_env(envp, (*vector)[(*index)]);
		if (env)
		{
			vector_replace((*vector), (*index), env);
			tokenize_2(temp_cursor, (*vector)[(*index)++]);
		}
		else
			(*vector) = vector_delete_index((*vector), (*index));
	}
	else
		temp_cursor->next = ft_lstnew(ft_strdup((*vector)[(*index)++]));
}

void	env_expansion_v2elst(t_list **temp_expand, char ***vector, char **envp)
{
	int		index;
	t_list	*temp_cursor;

	(*temp_expand) = ft_lstnew(0);
	if (!(*vector))
		return ;
	index = 0;
	temp_cursor = (*temp_expand);
	while ((*vector) && (*vector)[index])
	{
		env_expansion_v2elst_str(temp_cursor, vector, &index, envp);
		while (temp_cursor->next)
			temp_cursor = temp_cursor->next;
	}
}

char	**env_expansion_string_vector(char *string)
{
	int		index;
	char	**vector;
	int		start;

	vector = 0;
	index = 0;
	start = 0;
	while (string[index])
	{
		if (string[index] == '$' && \
			(ft_isalpha(string[index + 1]) || string[index + 1] == '_'))
			env_expansion_envstring(string, &vector, &index, &start);
		else
			index++;
	}
	if (index != start)
		vector = vector_add(vector, &(string[start]));
	return (vector);
}
