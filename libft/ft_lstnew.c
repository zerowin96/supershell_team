/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:24:39 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/10 08:58:34 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)ml_malloc(sizeof(t_list) * 1);
	if (new_node == 0)
		return (new_node);
	new_node->next = 0;
	new_node->content = content;
	return (new_node);
}
