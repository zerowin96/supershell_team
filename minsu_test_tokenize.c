#include "test.h"

void qmark_expansion(t_list *list, int pres);
void env_expansion(t_list *list, char **envp);
char	*ft_strjoin2(const char *replace, const char *source, int start, int finish);

int	is_ifs(int c)
{
	return ((c == ' ' || c =='\n' || c == '\t'));
}

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

static int	is_separator(char *string)
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


void	partial_string(t_list *list, char *string, int start, int finish)
{
	char	*temp;

	temp = (char *)ft_calloc(finish - start + 2, sizeof(char));
	ft_memmove(temp, &string[start], finish - start + 1);
	ft_lstadd_back(&list, ft_lstnew(temp));
}

void	tokenize_expansion(t_list *list, char *string, int *index)
{
	int	start;
	int	finish;

	start = (*index);
	while (string[(*index)] != ' ' && string[(*index)] && \
	is_separator(&string[(*index)]) == 0)
	{
		(*index)++;
		if (string[(*index)] == '$')
			break ;
	}
	finish = (*index) - 1;
	partial_string(list, string, start, finish);
	(*index)--;
}

void	tokenize_space(t_list *list, char *string, int *index)
{
	int	start;
	int	finish;

	start = (*index);
	while (string[(*index)] != ' ' && string[(*index)] && \
	is_separator(&string[(*index)]) == 0 && string[(*index)] != '$')
		(*index)++;
	finish = (*index) - 1;
	partial_string(list, string, start, finish);
	(*index)--;
}

void	tokenize_separator(t_list *list, char *string, int *index)
{
	int	start;
	int	finish;

	start = (*index);
	(*index) += (is_separator(&string[(*index)]) - 1);
	finish = (*index);
	partial_string(list, string, start, finish);
}

void	tokenize(t_list *list, char *string)
{
	int		index;

	index = 0;
	while (string[index])
	{
		if (string[index] >= 9 && string[index] <= 13 || string[index] == ' ')
		{
			if (index)
				partial_string(list, " ", 0, 1);
			while (string[index] >= 9 && string[index] <= 13 || string[index] == ' ')
				index++;
		}
		if (is_separator(&string[index]))
			tokenize_separator(list, string, &index);
		else if (string[index] && string[index] == '$')
			tokenize_expansion(list, string, &index);
		else if (string[index] && string[index] != ' ')
			tokenize_space(list, string, &index);
		if (string[index] == 0)
			break ;
		index++;
	}
}

t_list *parsing(char *line, char **envp)
{
	t_list	*list;
	t_list	*now;

	list = ft_lstnew(0);
	tokenize(list, line);
	if (quote_check(list))
		return (0);
	env_expansion(list, envp);

	//TOKEN PRINT
	// printf("--------------------TOKENS\n");
	// now = list->next;
	// while (now)
	// {
	// 	printf("%s\n", now->content);
	// 	now = now->next;
	// }
	// printf("--------------------tokens are stored in linked list\n");
	return (list);
}

char	*listjoin(t_list *list)
{
	t_list	*cursor;
	char	*temp = 0;
	char	*temp1 = 0;

	cursor = list->next;
	temp1 = (char *)ft_calloc(1, sizeof(char));
	while (cursor)
	{
		temp = ft_strjoin(temp1, cursor->content);
		free(temp1);
		temp1 = temp;
		cursor = cursor->next;
		// printf("|%s|\n", temp);
	}
	return (temp);
}

t_list *first_parsing(char **line, char **envp, int prev_result)
{
	t_list	*list;
	t_list	*now;

	list = ft_lstnew(0);
	tokenize(list, *line);
	free(*line);
	if (quote_check(list))
	{
		//free_all_list(list);
		return (0);
		//::change the value of return into "command not found-ish"
	}
	qmark_expansion(list, prev_result);
	// printf("--------------------TOKENS\n");
	// now = list->next;
	// while (now)
	// {
	// 	printf("%s\n", now->content);
	// 	now = now->next;
	// }
	// printf("--------------------tokens are stored in linked list\n");
	env_expansion(list, envp);//, result);

	char *temp = listjoin(list);
	// printf("temp : $%s$\n", temp);
	free_list(list);
	list = ft_lstnew(0);
	tokenize(list, temp);
	// env_expansion(list, envp);
	*line = temp;


	//TOKEN PRINT
	// printf("--------------------TOKENS\n");
	// now = list->next;
	// while (now)
	// {
	// 	printf("%s\n", now->content);
	// 	now = now->next;
	// }
	// printf("--------------------tokens are stored in linked list\n");
	return (list);
}

char	*env_expansion_string_a_env(char **string, char **envp, char *temp)
{
	char	*temp2;
	int		index;

	temp2 = 0;
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], temp, ft_strlen(temp)) == 0)
		{
			temp2 = &(envp[index][ft_strlen(temp)]);
			break ;
		}
		index++;
	}
	return (temp2);
}

void	env_expansion_string_a(char **string, char **envp, int *index)
{
	int		start;
	int		finish;
	char	*temp[3];

	start = ++(*index);
	while (ft_isalpha((*string)[(*index)]) || ft_isdigit((*string)[(*index)]))
		(*index)++;
	finish = (*index) - 1;
	temp[0] = (char *)ft_calloc(finish - start + 3, sizeof(char));
	ft_memmove(temp[0], &(*string)[start], finish - start + 1);
	temp[0][finish - start + 1] = '=';
	temp[1] = env_expansion_string_a_env(string, envp, temp[0]);
	free(temp[0]);
	temp[2] = ft_strjoin2(temp[1], *string, start, finish);
	free(*string);
	*string = temp[2];
	(*index) = (start - 1) + ft_strlen(temp[1]);
}

void	env_expansion_string(char **string, char **envp)
{
	int	index;

	index = 0;
	if ((*string)[index] == '\'')
		return ;
	while ((*string)[index])
	{
		if ((*string)[index] == '$' && (*string)[index + 1])
			env_expansion_string_a(string, envp, &index);
		else
			index++;
	}
}

void	qmark_expansion_string(char **string, int previous_code)
{
	int		start;
	int		index;
	int		finish;
	char	*temp[3];

	index = 0;
	if ((*string)[index] == '\'')
		return ;
	while ((*string)[index])
	{
		if ((*string)[index] == '$' && (*string)[index + 1] == '?')
		{
			start = ++index;
			finish = index;
			temp[1] = ft_itoa(previous_code);
			temp[2] = ft_strjoin2(temp[1], *string, start, finish);
			free(*string);
			*string = temp[2];
			index = (start - 1) + ft_strlen(temp[1]);
			free(temp[1]);
			temp[1] = 0;
		}
		else
			index++;
	}
}

void	quote_trim(t_list *list)
{
	t_list	*cursor;
	int		lendex;
	char	*new_string;

	cursor = list->next;
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
	t_list	*cursor;
	t_list	*prev;

	cursor = list->next;
	prev = list;
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

void	free_space(t_list *list)
{
	t_list	*cursor;
	t_list	*prev;

	cursor = list->next;
	prev = list;
	while (cursor)
	{
		if (cursor->content && *((char *)(cursor->content)) == ' ')
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

// void	free_last_space(t_list *list)
// {
// 	t_list *cursor = list->next;

// 	while (1)
// 	{
// 		if (cursor == 0)
// 			return ;
// 		if (cursor->next == 0 && ((char *)(cursor->content))[0] == ' ' && !((char *)(cursor->content))[0])
// 		{
// 			free(cursor->content);
// 			free(cursor);
// 			cursor = list->next;
// 		}
// 		cursor = cursor->next;
// 	}
// }

void env_expansion(t_list *list, char **envp)
{
	char	*string;
	t_list	*cursor;

	cursor = list->next;
	while (cursor)
	{
		env_expansion_string(((char **)&(cursor->content)), envp);
		if (cursor)
			cursor = cursor->next;
	}
	// quote_trim(list);
	free_empty(list);
	// free_last_space(list);
}

void qmark_expansion(t_list *list, int pres)
{
	char	*string;
	t_list	*cursor;

	cursor = list->next;
	while (cursor)
	{
		qmark_expansion_string(((char **)&(cursor->content)), pres);
		if (cursor)
			cursor = cursor->next;
	}
	// quote_trim(list);
	free_empty(list);
}

char	*ft_strjoin2(const char *replace, const char *source, int start, int finish)
{
	char	temp[1];
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
