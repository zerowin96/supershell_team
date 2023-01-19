#include "test.h"

void env_expansion(t_list *list, char **envp);
char	*ft_strjoin2(const char *replace, const char *source, int start, int finish);

int	is_ifs(int c)
{
	return ((c == ' ' || c =='n' || c == '\t'));
}

static int is_separator(char *string)
{
	int	index = 0;

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
	{
		// pipe->pipe_cnt++;
		return (1);
	}
	else
		return (0);
	return (index);
}


void	partial_string(t_list *list, char *string, int start, int finish)
{
	char *temp;

	printf("partial string : %d~%d", start, finish);
	temp = (char *)ft_calloc(finish - start + 2, sizeof(char));
	ft_memmove(temp, &string[start], finish - start + 1);
	printf("  ....%s....\n", temp);
	ft_lstadd_back(&list, ft_lstnew(temp));
}

void	tokenize(t_list *list, char *string)
{
	int		start = 0;
	int		finish = 0;
	int		index = 0;

	index = 0;
	while (string[index])
	{
		while (string[index] >= 9 && string[index] <= 13)
			index++;
		if (is_separator(&string[index]))
		{
			start = index;
			index += (is_separator(&string[index]) - 1);
			finish = index;
			partial_string(list, string, start, finish);
		}
		else if (string[index] && string[index] != ' ' && string[index] == '$')
		{
			start = index;
			while (string[index] != ' ' && string[index] && \
			is_separator(&string[index]) == 0)
			{
				index++;
				if (string[index] == '$')
					break ;
			}
			finish = index - 1;
			partial_string(list, string, start, finish);
			index--;
		}
		else if (string[index] && string[index] != ' ')
		{
			start = index;
			while (string[index] != ' ' && string[index] && \
			is_separator(&string[index]) == 0 && string[index] != '$')
				index++;
			finish = index - 1;
			partial_string(list, string, start, finish);
			index--;
		}
		if (string[index] == 0)
			break ;
		index++;
	}
}

t_list *parsing(char *line, char **envp)
{
	//char *string = "	'cat -e'"|	 ls -al | while || <<< >> ls ls ls lslsls ><\" \"||$123|\'\'//..,,>>><<<\"\" ppplll>>>lllsss$USERpsdl$user | >>>$hello";
	// char *string = "ppplll\'>>>\'lllsss";
	t_list *list;
	t_list *now;

	list = ft_lstnew(0);
	tokenize(list, line);
	env_expansion(list, envp);

	printf("--------------------TOKENS\n");
	now = list->next;
	while (now)
	{
		printf("%s\n", now->content);
		now = now->next;
	}
	printf("--------------------tokens are stored in linked list\n");
	return (list);
}










void	env_expansion_string(char **string, char **envp)
{
	int start = 0;
	int index = 0;
	int	finish = 0;
	int	i = 0;

	// char *temp;

	char 	*temp;
	char	*temp2;
	char	*temp3;

	// if (*string && **string && (**string != '\'' && **string != '>' && **string != '|' && **string != '<'))
	// {
			

		while ((*string)[index])
		{
			while ((*string)[index] != '$' && (*string)[index])
			{
				if((*string)[index] == '\'')
				{
					index++;
					while ((*string)[index] != '\'')
						index++;
					index++;
				}
				else
					index++;
			}
			if ((*string)[index] == '$')
			{
				start = ++index;
				while (ft_isalpha((*string)[index]) || ft_isdigit((*string)[index]))
					index++;
				finish = index - 1;
				temp = (char *)ft_calloc(finish - start + 3, sizeof(char));
				ft_memmove(temp, &(*string)[start], finish - start + 1);
				temp[finish - start + 1] = '=';
				// printf("finding : %s\n", temp);
				temp2 = 0;
				while(envp[i])
				{
					if (ft_strncmp(envp[i], temp, ft_strlen(temp)) == 0)
					{
						temp2 = &(envp[i][ft_strlen(temp)]);
						break ;
					}
					i++;
				}
				free(temp);
				// printf("its key : %s\n", temp2);
				temp3 = ft_strjoin2(temp2, *string, start, finish);
				free(*string);
				*string = temp3;
				// cursor->content = temp3;
				index = (start - 1) + ft_strlen(temp2);
				temp2 = 0;
			}
		// }
	}
}

void	quote_trim(t_list *list)
{
	t_list *cursor = list->next;
	t_list	*prev = list;
	int		lendex = 0;
	char	*new_string = 0;

	while (cursor)
	{
		if (cursor->content && (((char *)(cursor->content))[0] == '\'' || ((char *)(cursor->content))[0] == '\"'))
		{
			lendex = ft_strlen((char *)cursor->content);
			new_string = (char *)ft_calloc(lendex - 1, sizeof(char));
			ft_memmove(new_string, &(((char *)(cursor->content))[1]), lendex - 2);
			new_string[lendex] = 0;
			free(cursor->content);
			cursor->content = 0;
			cursor->content = new_string;
		}
		cursor = cursor->next;
	}
}

void	free_empty(t_list *list)
{
	t_list *cursor = list->next;
	t_list *prev = list;
	while (cursor)
	{
		if (cursor->content == 0 || *((char *)(cursor->content)) == 0)
		{
			prev->next = cursor->next;
			if (cursor->content)
				free(cursor->content);
			free(cursor);
			cursor = prev->next;
		}
		if (cursor)
		{
			cursor = cursor->next;
			prev = prev->next;
		}
	}
}

void env_expansion(t_list *list, char **envp)
{
	char	*string;
	t_list	*cursor;
	// int		index;
	// int		start;
	// int		finish;
	// int		i = 0;

	// char 	*temp;
	// char	*temp2;
	// char	*temp3;
	cursor = list->next;
	
	while (cursor)
	{
		// printf("CURSOR WHILE LOOP\n");
		// index = 0;
		string = cursor->content;
		env_expansion_string(((char **)&(cursor->content)), envp);
		if (cursor)
			cursor = cursor->next;
	}
	
	// quote_trim(list);
	free_empty(list);
}

char	*ft_strjoin2(const char *replace, const char *source, int start, int finish)
{
	char temp[1];
	int		len;
	char	*ret_str;

	temp[0] = 0;
	if (!replace)
		replace = temp;
	len = (ft_strlen(source) - 1) - (finish - start + 1 ) + ft_strlen(replace) + 1;
	ret_str = (char *)ft_calloc(len, sizeof(char));
	ft_memmove(ret_str, source, start - 1);
	if (replace)
		ft_memmove(&ret_str[start - 1], replace, ft_strlen(replace));
	ft_memmove(&ret_str[ft_strlen(ret_str)], &source[finish + 1], ft_strlen(&source[finish + 1]));
	return (ret_str);
}
