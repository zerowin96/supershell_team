/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:56:08 by yeham             #+#    #+#             */
/*   Updated: 2023/01/13 16:22:26 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (*ss1 && *ss2)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
	}
	return (*ss1 - *ss2);
}

void	export_print(char **sorted_envp)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (sorted_envp[i])
	{
		write(1, "declare -x ", 11);
		j = 0;
		flag = 0;
		while (sorted_envp[i][j])
		{
			write(1, &sorted_envp[i][j], 1);
			if (sorted_envp[i][j] == '=' && flag == 0)
			{
				write(1, "\"", 1);
				flag = 1;
			}
			j++;
		}
		if (flag == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

void	sort_and_print(t_copy *env)
{
	int		i;
	int		j;
	char	*temp;
	char	**sorted_envp;

	sorted_envp = env->cp_envp;
	i = 0;
	while (sorted_envp[i++])
	{
		j = 0;
		while (sorted_envp[j + 1])
		{
			if (ft_strcmp(sorted_envp[j], sorted_envp[j + 1]) > 0)
			{
				temp = sorted_envp[j];
				sorted_envp[j] = sorted_envp[j + 1];
				sorted_envp[j + 1] = temp;
			}
			j++;
		}
	}
	export_print(sorted_envp);
}

void trim_test(t_list *cursor)
{
	int i;
	cursor = cursor->next;

	while (cursor)
	{
		i = 0;
		while (((char *)(cursor->content))[i])
		{
			if (((char *)(cursor->content))[i] == '\'' || ((char *)(cursor->content))[i] == '\"')
			{
				printf("check\n");
				while (((char *)(cursor->content))[i + 1])
				{
					((char *)(cursor->content))[i] = ((char *)(cursor->content))[i + 1];
					i++;
				}
				((char *)(cursor->content))[i - 1] = '\0';
				break ;
			}
			i++;
		}
		printf("trim test === %s\n", cursor->content);
		cursor = cursor->next;
	}
}


void ft_export(char *line, t_list *node, t_copy *env)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int flag = 0;
	char *string;
	char **fuck;
	t_list *a, *test_a;
	a = ft_lstnew(0);

	fuck = env_split(line);
	while(fuck[k])
	{
		env_expansion_string(&(fuck[k]), env->cp_envp);
		ft_lstadd_back(&a, ft_lstnew(fuck[k]));
		k++;
	}
	trim_test(a);
	test_a = a->next;
	if (test_a->next == NULL)
	{
		sort_and_print(env);
		return ;
	}
	else
	{
		while (test_a->next)
		{
			i = 0;
			j = 0;
			flag = 0;
			string = (test_a->next->content);
			while (string[j])
			{
				if (string[j] == '=')
				{
					flag = 1;
					while (env->cp_envp[i])
					{
						if (ft_strncmp(env->cp_envp[i], string, j) == 0)
						{
							env->cp_envp[i] = string;
							flag = 2;
							break ;
						}
						i++;
					}
					if (flag == 1)
					{
						env->cp_envp[i] = string;
						env->cp_envp[i + 1] = 0;
					}
					break ;
				}
				j++;
			}
			if (flag == 0)
			{
				i = 0;
				while (env->cp_envp[i])
				{
					if (ft_strncmp(env->cp_envp[i], string, \
						ft_strlen(string)) == 0)
					{
						flag = 3;
						break ;
					}
					i++;
				}
				if (flag == 0)
				{
					env->cp_envp[i] = string;
					env->cp_envp[i + 1] = 0;
				}
			}
			test_a = test_a->next;
		}
	}
}