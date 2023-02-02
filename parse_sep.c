/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:30:54 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/02 18:41:47 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	is_separator_quote(char *string)
{
	int	index;

	index = 0;
	if (string[index] == '\'')
	{
		index++;
		while (string[index] != '\'' && string[index])
			index++;
		index++;
	}
	else if (string[index] == '\"')
	{
		index++;
		while (string[index] != '\"' && string[index])
			index++;
		index++;
	}
	return (index);
}

int	is_separator(char *string)
{
	int	index;

	index = 0;
	if (string[index] == '\'' || string[index] == '\"')
		return (is_separator_quote(string));
	else if (string[index] == '>')
	{
		index++;
		if (string[index] == '>')
			index++;
	}
	else if (string[index] == '<')
	{
		index++;
		if (string[index] == '<')
			index++;
	}
	else if (string[index] == '|')
		return (1);
	else
		return (0);
	return (index);
}
