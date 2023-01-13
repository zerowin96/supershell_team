#include "test.h"

void	vector_free(char **vector)
{
	int	index;
	if (!(vector))
		return ;
	index = 0;
	while (vector[index])
	{
		free(vector[index]);
		vector[index] = 0;
		index++;
	}
	free(vector);
	// *vector = 0;
}

int		string_compare(char *string, char *compare)
{
	int	index;

	index = 0;
	while (string[index] && string[index] == compare[index]) // && compare[index]는, 선행 두 조건 만족시 무조건 만족해야 함.
	{
		index++;
	}
	return (string[index] - compare[index]);
	// 음수이면 string이 compare보다 사전상 앞에 있는 것.
}

int		get_vector_len(char **vector)
{
	int index = 0;
	if (!vector)
		return (0);
	while (vector[index])
		index++;
	return (index);
}

// char	**vector_delete_element(char **vector, char *string)
// {
// 	char **new_vector;
// 	int	index = 0;
// 	int	delete_index = -1;

// 	if (!vector)
// 		return (vector);
// 	while (vector[index])
// 	{
// 		delete_index = string_compare(vector[index], string);
// 		if (delete_index == 0)
// 		{
// 			delete_index = index;
// 			break;
// 		}
// 		index++;
// 	}
// 	if (vector[index] == 0)
// 		return (vector);
// 	new_vector = (char **)ft_calloc(get_vector_len(vector), sizeof(char *));
// 	index = 0;
// 	while (vector[index])
// 	{
// 		if (index > delete_index)
// 			new_vector[index - 1] = vector[index];
// 		else
// 			new_vector[index] = vector[index];
// 		index++;
// 	}
// 	free(vector[delete_index]);
// 	free(vector);
// 	return (new_vector);
// }

char	**vector_delete_index(char **vector, int delete_index)
{
	char **new_vector;
	int	index = 0;

	if (!vector)
		return (vector);
	if (!get_vector_len(vector) || (get_vector_len(vector) <= delete_index))
		return (vector);
	if (get_vector_len(vector) == 1)
	{
		vector_free(vector);
		return (0);
	}
	new_vector = (char **)ft_calloc(get_vector_len(vector), sizeof(char *));
	while (vector[index])
	{
		if (index > delete_index)
			new_vector[index - 1] = vector[index];
		else
			new_vector[index] = vector[index];
		index++;
	}
	new_vector[index - 1] = vector[index];
	// vector_free(vector);
	
	free(vector[delete_index]);
	vector[delete_index] = 0;
	free(vector);
	vector = 0;
	return (new_vector);
}

// int		vector_sort_check(char **vector)
// {
// 	int index = 1;
// 	while (vector[index])
// 	{
// 		if (string_compare(vector[index - 1], vector[index]) < 0)
// 			break ;
// 		index++;
// 	}
// 	if (vector[index] == 0)
// 		return (1);
// 	else
// 		return (0);
// }


// char	**vector_sort(char **vector)
// {

// }



char	**vector_add(char **vector, char *string)
{
	char **new_vector;
	int index;

	new_vector = (char **)ft_calloc(get_vector_len(vector) + 2, sizeof(char *));
	index = 0;
	if (vector)
	{
		while (vector[index])
		{
			new_vector[index] = vector[index];
			index++;
		}
	}
	new_vector[index] = string;
	// new_vector[index + 1] = 0; // ft_calloc이므로 없어도 괜찮다.
	// vector_free(vector);
	free(vector);
	// vector = 0;

	return (new_vector);
}

void	vector_print(char **vector)
{
	int index = 0;
	if (!vector || !(vector[0]))
	{
		printf("vector is empty\n");
		return ;
	}
	printf("--------------------vector print start\n");
	while (vector[index])
	{
		printf("%s\n", vector[index]);
		index++;
	}
	printf("--------------------vector print finished\n");
}

void	vector_replace(char **vector, int replace_index, char *replace_string)
{
	if (replace_index >= get_vector_len(vector))
		return ;
	free(vector[replace_index]);
	vector[replace_index] = replace_string;
}

// int main(void)
// {
// 	char **vector = 0;
// 	char *string[100];

// 	// *vector = 0;
// 	vector_print(vector);

// 	// string[1] = ft_strdup("string one");
// 	vector = vector_add(vector, ft_strdup("string one"));
// 	// vector_print(vector);
// 	// string[2] = ft_strdup("string two");
// 	// vector = vector_add(vector, string[2]);
// 	// vector_print(vector);
// 	// string[3] = ft_strdup("string three");
// 	// vector = vector_add(vector, string[3]);
// 	// vector_print(vector);
// 	// vector = vector_delete_index(vector, 1);
// 	// vector_print(vector);
// 	vector_print(vector);
// 	vector = vector_delete_index(vector, 0);
// 	vector_print(vector);
// 	vector = vector_delete_index(vector, 0);
// 	vector_print(vector);
// 	vector_free(vector);
// }