/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:32:31 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 20:02:50 by minsulee         ###   ########seoul.kr  */
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
	while (ft_isalpha((*string)[(*index)]) || ft_isdigit((*string)[(*index)]))
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

void	env_expansion_string(char **string, char **envp)
{
	int	index;

	index = 0;
	if ((*string)[index] == '\'')
		return ;
	while ((*string)[index])
	{
		if ((*string)[index] == '$' && (*string)[index + 1])
			env_expansion_string_a(string, envp, &index);
		else
			index++;
	}
}

void	env_expansion(t_list *list, char **envp)
{
	t_list	*cursor;

	cursor = list->next;
	while (cursor)
	{
		env_expansion_string(((char **)&(cursor->content)), envp);
		if (cursor)
			cursor = cursor->next;
	}
	free_empty(list);
}
