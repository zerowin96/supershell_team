#include "test.h"

int main(int argc, char **argv, char **envp)
{
	int i;
	t_copy **env;
	char *temp;

	i = 0;
	temp = "sexy";

	for (int j = 0; envp[j]; j++)
	{
		env[j] = envp[j];
	}
	while (env[i])
	{
		printf("%s /// %s\n", env[i], temp);
		if (ft_strncmp(envp[i], temp, ft_strlen(temp)) == 0)
		{
			printf("%s /// %s\n", env[i], temp);
			env[i] = ft_strdup("fuck");
			printf("change == %s\n", env[i]);
			printf("get env == %s\n", getenv(temp));
			break ;
		}
		i++;
	}
	return (argc);
}