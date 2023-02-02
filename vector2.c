/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:26:56 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 18:38:00 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	vector_replace(char **vector, int replace_index, char *replace_string)
{
	if (replace_index >= get_vector_len(vector))
		return ;
	free(vector[replace_index]);
	vector[replace_index] = ft_strdup(replace_string);
}

void	vector_replace2(char **vector, int replace_index, char *replace_string)
{
	if (replace_index >= get_vector_len(vector))
		return ;
	free(vector[replace_index]);
	vector[replace_index] = ft_strdup(replace_string);
	free(replace_string);
}
