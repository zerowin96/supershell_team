/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:26:59 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 18:56:39 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	vector_free(char **vector)
{
	int	index;

	index = 0;
	if (!(vector))
		return ;
	while (vector[index])
	{
		free(vector[index]);
		index++;
	}
	free(vector);
}

int	get_vector_len(char **vector)
{
	int	index;

	index = 0;
	if (!vector)
		return (0);
	while (vector[index])
		index++;
	return (index);
}

char	**vector_delete_index(char **vector, int delete_index)
{
	char	**new_vector;
	int		index;

	index = 0;
	if (!vector || !get_vector_len(vector) || (get_vector_len(vector) <= delete_index))
		return (vector);
	if (get_vector_len(vector) == 1)
	{
		vector_free(vector);
		return (0);
	}
	new_vector = (char **)ft_calloc(get_vector_len(vector), sizeof(char *));
	while (vector[index])
	{
		if (index > delete_index)
			new_vector[index - 1] = vector[index];
		else
			new_vector[index] = vector[index];
		index++;
	}
	new_vector[index - 1] = vector[index];
	free(vector[delete_index]);
	free(vector);
	return (new_vector);
}

char	**vector_add(char **vector, char *string)
{
	char	**new_vector;
	int		index;

	index = 0;
	new_vector = (char **)ft_calloc(get_vector_len(vector) + 2, sizeof(char *));
	if (vector)
	{
		while (vector[index])
		{
			new_vector[index] = ft_strdup(vector[index]);
			index++;
		}
	}
	new_vector[index] = ft_strdup(string);
	vector_free(vector);
	return (new_vector);
}
