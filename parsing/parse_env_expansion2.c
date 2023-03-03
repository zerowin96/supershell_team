/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_expansion2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:50:08 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 13:51:40 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	env_expansion_lstcon(t_list **temp_expand, t_list **cursor)
{
	t_list	*new;
	t_list	*old_last;
	t_list	*new_last;

	new = (*temp_expand);
	if (new == 0)
	{
		free((*temp_expand)->content);
		free((*temp_expand));
		free((*cursor)->content);
		(*cursor)->content = ft_strdup("");
		(*cursor) = (*cursor)->next;
		return ;
	}
	old_last = (*cursor)->next;
	new_last = new;
	while (new_last->next)
		new_last = new_last->next;
	new_last->next = old_last;
	free((*cursor)->content);
	(*cursor)->content = new->content;
	(*cursor)->next = new->next;
	(*cursor) = old_last;
	free(new);
}

void	env_expansion_string(t_list **cursor, char **envp)
{
	char	**vector;
	char	*string;
	t_list	*temp_expand;

	string = (*cursor)->content;
	vector = 0;
	if (string[0] == '\'')
	{
		(*cursor) = (*cursor)->next;
		return ;
	}
	vector = env_expansion_string_vector(string);
	env_expansion_v2elst(&temp_expand, &vector, envp);
	vector_free(vector);
	list_tie(temp_expand);
	env_expansion_lstcon(&temp_expand, cursor);
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
			continue ;
		}
		if (!ft_strncmp(cursor->content, " ", 2))
		{
			cursor = cursor->next;
			continue ;
		}
		env_expansion_string(&cursor, envp);
	}
}
