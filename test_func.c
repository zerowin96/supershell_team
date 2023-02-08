#include "main.h"

// void	vector_print(char *string, char **vector);
// void	list_print(char *string, t_list *list);
// char	*listjoin(t_list *list);


void	list_print(char *string, t_list *list)
{
	printf("%s\n", string);
	t_list	*print_temp;
	print_temp = list;
	int index = 0;
	// printf("__________\n");
	while (print_temp)
	{
		// if (print_temp == print_temp->next)
		// {
		// 	printf("warning!!!!!\n");
		// 	return ;
		// }
		printf("%16s$ %4zu %16p, %16p %16p  \n", print_temp->content, ft_strlen(print_temp->content), print_temp, print_temp->content, print_temp->next);
		print_temp = print_temp->next;
		index++;
		// sleep(1);
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
		// printf("vector_to_list : put $%s$ into list\n", (*vector)[index]);
		ft_lstadd_back(&list, ft_lstnew((*vector)[index]));
		index++;
	}
	// return (list);
	t_list *temp = 0;
	// temp = list->next;
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
		// finish = index; //index == null이나 whitespace
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
	// vector_print("whitespace_split +++++++++++++++++++", split);
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
			// vector_print("whitespace vector print", vector);
			// vector = list_to_vector(list);
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














			// vector_free(vector);
			free(vector);
			vector = 0;
			// list_print("f++++++++++++++++++++++++++++++++++++++++++++++++ ", head);
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
		// printf("%s\n", tie_temp->content);
		if (tie_temp->content == 0 || tie_prev->content == 0)
		{
			tie_prev = tie_temp;
			tie_temp = tie_prev->next;
			continue;
		}
		// if (((char *)(tie_temp->content))[0] == 0)
		// {
		// 	tie_prev->next = tie_temp->next;
		// 	free(tie_temp->content);
		// 	tie_temp->content = 0;
		// 	free(tie_temp);
		// 	tie_temp = tie_prev->next;
		// }
		// else if (ft_strncmp(tie_prev->content, " ", 2) == 0 \
		&& ft_strncmp(tie_temp->content, " ", 2) == 0)
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

// void		quote_trim(t_list *list);

// void	list_print(char *string, t_list *list)
// {
// 	printf("%s\n", string);
// 	t_list	*print_temp;
// 	print_temp = list->next;
// 	int index = 0;
// 	// printf("__________\n");
// 	while (print_temp)
// 	{
// 		printf("%s$  ", print_temp->content);
// 		print_temp = print_temp->next;
// 		index++;
// 	}
// 	printf("\n");
// 	printf("==========\n");
// }



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

void	list_tie_2(t_list *temp)
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
		// printf("%s\n", tie_temp->content);
		if (tie_temp->content == 0 || tie_prev->content == 0)
		{
			tie_prev = tie_temp;
			tie_temp = tie_prev->next;
			continue;
		}
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
}