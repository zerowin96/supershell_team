/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_util_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:23:37 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/03 13:33:32 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	quote_out_command_one(char ***command)
{
	char	*temp_string;

	if ((**command)[0] == (**command)[ft_strlen((**command)) - 1] \
	&& ((**command)[0] == '\'' || (**command)[0] == '\"'))
	{
		temp_string = ft_strdup(&(**command)[1]);
		temp_string[ft_strlen(temp_string) - 1] = 0;
	}
	else
		temp_string = ft_strdup((**command));
	free(**command);
	**command = temp_string;
}

void	quote_out_command_unhead(char ***command)
{
	int		index;
	char	*temp_string;

	index = 1;
	if ((*command)[0] == 0)
		return ;
	while ((*command)[index])
	{
		if ((*command)[index][0] == \
		(*command)[index][ft_strlen(((*command)[index])) - 1] \
		&& ((*command)[index][0] == '\'' || (*command)[index][0] == '\"'))
		{
			temp_string = ft_strdup(&((*command)[index][1]));
			temp_string[ft_strlen(temp_string) - 1] = 0;
		}
		else
		{
			temp_string = ft_strdup((*command)[index]);
		}
		free ((*command)[index]);
		(*command)[index] = temp_string;
		index++;
	}
}

int	quote_check(t_list *list)
{
	int	len;

	while (list->next)
		list = list->next;
	if (!(list) || !(list->content))
		return (1);
	len = ft_strlen((char *)(list->content));
	if (((char *)(list->content))[0] == '\'')
	{
		if (((char *)(list->content))[len - 1] != '\'' || len == 1)
			printf("minishell: quote not closed: close quote\n");
		else
			return (1);
	}
	else if (((char *)(list->content))[0] == '\"')
	{
		if (((char *)(list->content))[len - 1] != '\"' || len == 1)
			printf("minishell: quote not closed: close quote\n");
		else
			return (1);
	}
	else
		return (0);
	return (1);
}
