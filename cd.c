/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:07:18 by yeham             #+#    #+#             */
/*   Updated: 2023/02/01 21:05:50 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*get_pwd(t_copy *env)
{
	int	i;

	i = 0;
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], "PWD=", 4) == 0)
			return (env->cp_envp[i] + 4);
		i++;
	}
	return (0);
}

char	*get_home(t_copy *env)
{
	int	i;

	i = 0;
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], "HOME=", 5) == 0)
			return (env->cp_envp[i] + 5);
		i++;
	}
	return (0);
}

void	change_oldpwd(t_copy *env)
{
	char	*env_pwd;
	int		i;

	i = 0;
	env_pwd = get_pwd(env);
	while (env->cp_envp[i] && env->onlyenv[i])
	{
		if (ft_strncmp(env->cp_envp[i], "OLDPWD=", 7) == 0)
			vector_replace2(env->cp_envp, i, ft_strjoin("OLDPWD=", env_pwd));
		if (ft_strncmp(env->onlyenv[i], "OLDPWD=", 7) == 0)
			vector_replace2(env->onlyenv, i, ft_strjoin("OLDPWD=", env_pwd));
		i++;
	}
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], "OLDPWD=", 7) == 0)
			vector_replace2(env->cp_envp, i, ft_strjoin("OLDPWD=", env_pwd));
		i++;
	}
	while (env->onlyenv[i])
	{
		if (ft_strncmp(env->onlyenv[i], "OLDPWD=", 7) == 0)
			vector_replace2(env->onlyenv, i, ft_strjoin("OLDPWD=", env_pwd));
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
			vector_replace2(env->cp_envp, i, ft_strjoin("PWD=", pwd));
		if (ft_strncmp(env->onlyenv[i], "PWD=", 4) == 0)
			vector_replace2(env->onlyenv, i, ft_strjoin("PWD=", pwd));
		i++;
	}
	while (env->cp_envp[i])
	{
		if (ft_strncmp(env->cp_envp[i], "PWD=", 4) == 0)
			vector_replace2(env->cp_envp, i, ft_strjoin("PWD=", pwd));
		i++;
	}
	while (env->onlyenv[i])
	{
		if (ft_strncmp(env->onlyenv[i], "PWD=", 4) == 0)
			vector_replace2(env->onlyenv, i, ft_strjoin("PWD=", pwd));
		i++;
	}
}

void	ft_cd(char *next, t_copy *env)
{
	char	*now;
	char	*env_home;

	env_home = get_home(env);
	if (next == NULL && chdir(env_home) == 0)
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
		perror("No such file o directory\n");
	}
}
