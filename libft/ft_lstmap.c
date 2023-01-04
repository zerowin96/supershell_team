/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:46:39 by minsulee          #+#    #+#             */
/*   Updated: 2022/07/20 13:30:48 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;
	int		sign;

	if (lst == 0)
		return (0);
	sign = 0;
	new_lst = ft_lstnew(f(lst->content));
	if (new_lst == 0)
		return (0);
	temp = new_lst;
	lst = lst->next;
	while (lst != 0)
	{
		new_lst->next = ft_lstnew(f(lst->content));
		if (new_lst->next == 0)
		{
			ft_lstclear(&temp, del);
			return (0);
		}
		lst = lst->next;
		new_lst = new_lst->next;
	}
	new_lst->next = 0;
	return (temp);
}
