/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:44:52 by yeham             #+#    #+#             */
/*   Updated: 2023/02/02 18:27:34 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = 0;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}
