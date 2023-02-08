#include "main.h"

void	list_print(char *string, t_list *list)
{
	printf("%s\n", string);
	t_list	*print_temp;
	print_temp = list;
	int index = 0;
	while (print_temp)
	{
		printf("%16s$ %4zu %16p, %16p %16p  \n", print_temp->content, ft_strlen(print_temp->content), print_temp, print_temp->content, print_temp->next);
		print_temp = print_temp->next;
		index++;
	}
	printf("\n");
	printf("==========\n");
}


t_list *vector_to_list(char ***vector)
{
	t_list	*list;

	list = ft_lstnew(0);
	if (!vector || !(*vector))
		return (0);

	int index = 0;
	while ((*vector)[index])
	{
		ft_lstadd_back(&list, ft_lstnew((*vector)[index]));
		index++;
	}
	t_list *temp = 0;
	if (list->next)
		temp = list->next;
	free(list->content);
	list->content = 0;
	free(list);
	list = 0;
	return (temp);
}

char	**list_to_vector(t_list *list)
{
	char **vector;

	vector = 0;
	if (!list->content || (ft_strlen(list->content) == 1 && ((char *)(list->content))[0] == ' '))
		list = list->next;
	while (list)
	{
		vector = vector_add(vector, list->content);
		list = list->next;
	}
	return (vector);
}

int		ml_iswhite(char c)
{
	if (c == ' ')
		return (1);
	else if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

char	**whitespace_split(char *string)
{
	int	start;
	int	finish;
	int	index;
	char	**split;

	split = 0;
	index = 0;
	finish = 0;
	if (string == 0)
		return (0);
	while (string[index])
	{
		if (ml_iswhite(string[index]))
			split = vector_add(split, " ");
		while (ml_iswhite(string[index]))
			index++;
		start = index;
		while (!(ml_iswhite(string[index])) && string[index])
			index++;
		if (string[index] == 0)
			finish = 1;
		string[index] = 0;
		split = vector_add(split, &(string[start]));
		if (finish == 0)
			split = vector_add(split, " ");
		index++;
		if (finish)
			break;
	}
	return (split);
}

void	list_whitespace_split(t_list *list)
{
	t_list	*head = list->next;
	t_list	*prev = list;
	list = list->next;
	int start;
	int finish;
	t_list *temp[2];
	char	**vector;


	while (list)
	{
		if (!(list->content))
		{
			prev->next = list->next;
			free(list);
			list = prev->next;
			continue;
		}
		int len = ft_strlen(list->content);
		if ((((char *)(list->content))[0] == '\'' \
		|| ((char *)(list->content))[0] == '\"') && ((char *)(list->content))[0] == ((char *)(list->content))[len - 1])
		{
			;
		}
		else
		{
			vector = whitespace_split(list->content);
			temp[0] = vector_to_list(&vector);
			temp[1] = list->next;

			prev->next = temp[0];
			free(list->content);
			list->content = 0;
			free(list);
			list = temp[1];
			while (prev->next)
				prev = prev->next;
			prev->next = list;
			free(vector);
			vector = 0;
			continue;
		}
		prev = list;
		list = list->next;
	}
}

void	list_tie(t_list *temp)
{
	t_list	*tie_temp;
	t_list	*tie_prev;
	t_list	*list = temp;
	if (!list->next)
		return ;
	tie_temp = list->next->next;
	tie_prev = list->next;
	while(tie_temp)
	{
		if (tie_temp->content == 0 || tie_prev->content == 0)
		{
			tie_prev = tie_temp;
			tie_temp = tie_prev->next;
			continue;
		}
		if (ft_strncmp(tie_prev->content, " ", 2) \
		&& ft_strncmp(tie_temp->content, " ", 2))
		{
			char	*temp_string;
			temp_string = ft_strjoin(tie_prev->content, tie_temp->content);
			free (tie_prev->content);
			tie_prev->content = temp_string;
			tie_prev->next = tie_temp->next;
			free(tie_temp->content);
			tie_temp->content = 0;
			free(tie_temp);
			tie_temp = tie_prev->next;
		}
		else
		{
			tie_prev = tie_temp;
			tie_temp = tie_prev->next;
		}
	}
}

void	vector_print(char *string, char **vector)
{
	printf("%s\n", string);
	int index = 0;
	printf("__________\n");
	if (vector)
	{
		while(vector[index])
		{
			printf("%s$  ", vector[index]);
			index++;
		}
	}
	printf("\n");
	printf("==========\n");
}
