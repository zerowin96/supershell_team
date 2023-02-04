/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child_checkaccess.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:14:40 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/03 14:43:18 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_access_h(char *name, char *path, int permission)
{
	char	*temp;
	char	*temp2;
	int		index;

	temp2 = 0;
	temp = 0;
	index = 0;
	if (name == 0)
		return (0);
	if (path != 0)
	{
		temp2 = ft_strjoin(path, "/");
		temp = ft_strjoin(temp2, name);
		free(temp2);
	}
	if (path == 0)
		temp = name;
	if (access(temp, permission) == 0)
		index = 1;
	if (path != 0)
	{
		free(temp);
		temp = 0;
	}
	return (index);
}

int	check_access(char *name, char **paths, int permission)
{
	int	index;

	index = 0;
	if (!paths)
		return (0);
	while (paths[index])
	{
		if (check_access_h(name, paths[index], permission))
			return (index + 2);
		index++;
	}
	if (check_access_h(name, 0, permission))
	{
		if (name[0] == '.' && name[1] == '/')
			return (1);
		else if (name[0] == '/')
			return (1);
	}
	return (0);
}


