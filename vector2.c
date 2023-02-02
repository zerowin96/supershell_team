#include "test.h"

void	vector_replace(char **vector, int replace_index, char *replace_string)
{
	if (replace_index >= get_vector_len(vector))
		return ;
	free(vector[replace_index]);
	vector[replace_index] = ft_strdup(replace_string);
}

void	vector_replace2(char **vector, int replace_index, char *replace_string)
{
	if (replace_index >= get_vector_len(vector))
		return ;
	free(vector[replace_index]);
	vector[replace_index] = ft_strdup(replace_string);
	free(replace_string);
}
