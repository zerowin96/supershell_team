#include "test.h"

int get_filename(void)
{
	char	*string;
	int		index;
	int		len;

	string = (char *)ft_calloc(10, sizeof(char));
	string[0] = '0';
	while (access(string, F_OK) == 0)
	{
		index = 0;
		string[0]++;
		len = ft_strlen(string);
		while (index < len)
		{
			if (string[index] == 127)
			{
				string[index] = '0';
				string[index + 1]++;
				if(index + 1 == len)
					len++;
			}
			if (string[index] < '0')
				string[index] = '0';
			index++;
		}
		printf("%s\n", string);
	}
	return (string);
}


// 1. 들어온 string check;
// 2. 들어온 string 이 ~~~(126) 이면 ~~~\0으로 만들어 주기 (늘리기)
// 3. string[0]++;
// 4. index를 보며 만약 string[index] == 127 이면 string[index + 1]++.
// 5. string[index] < '0' 이면 string[index] = 0;

