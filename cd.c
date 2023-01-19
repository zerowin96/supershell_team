/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:07:18 by yeham             #+#    #+#             */
/*   Updated: 2023/01/18 20:30:02 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	change_oldpwd(t_copy *env)
{
	int	i;

	i = 0;
	while (env->cp_envp[i] && env->onlyenv[i])
	{
		if (ft_strncmp(env->cp_envp[i], "OLDPWD=", 7) == 0)
			env->cp_envp[i] = ft_strjoin("OLDPWD=", getenv("PWD"));
		if (ft_strncmp(env->onlyenv[i], "OLDPWD=", 7) == 0)
			env->onlyenv[i] = ft_strjoin("OLDPWD=", getenv("PWD"));
		i++;
	}
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], "OLDPWD=", 7) == 0)
			env->cp_envp[i] = ft_strjoin("OLDPWD=", getenv("PWD"));
		i++;
	}
	while (env->onlyenv[i])
	{
		if (ft_strncmp(env->onlyenv[i], "OLDPWD=", 7) == 0)
			env->onlyenv[i] = ft_strjoin("OLDPWD=", getenv("PWD"));
		i++;
	}
}

void	change_pwd(t_copy *env, char *pwd)
{
	int	i;

	i = 0;
	while (env->cp_envp[i] && env->onlyenv[i])
	{
		if (ft_strncmp(env->cp_envp[i], "PWD=", 4) == 0)
			env->cp_envp[i] = ft_strjoin("PWD=", pwd);
		if (ft_strncmp(env->onlyenv[i], "PWD=", 4) == 0)
			env->onlyenv[i] = ft_strjoin("PWD=", pwd);
		i++;
	}
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], "pwd=", 4) == 0)
			env->cp_envp[i] = ft_strjoin("pwd=", getenv("PWD"));
		i++;
	}
	while (env->onlyenv[i])
	{
		if (ft_strncmp(env->onlyenv[i], "pwd=", 4) == 0)
			env->onlyenv[i] = ft_strjoin("pwd=", getenv("PWD"));
		i++;
	}
}

void	ft_cd(char *next, t_copy *env)
{
	char	*now;

	if (next == NULL && chdir(getenv("HOME")) == 0)
	{
		now = getcwd(NULL, 0);
		change_oldpwd(env);
		change_pwd(env, now);
		free(now);
	}
	else if (chdir(next) == 0)
	{
		now = getcwd(NULL, 0);
		change_oldpwd(env);
		change_pwd(env, now);
		free(now);
	}
	else
	{
		printf("없을때!!\n");
		perror("No such file o directory\n");
	}
}
