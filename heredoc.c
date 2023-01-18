#include "test.h"
// #include <unistd.h>
char *get_filename(void);




void	here_doc_help2(int fd, char *limiter)
{
	char	*line;
	char	*mod_limiter;
	int		len;

	len = ft_strlen(limiter);
	mod_limiter = (char *)ft_calloc(len + 2, sizeof(char));
	ft_memmove(mod_limiter, limiter, len);
	mod_limiter[len] = '\n';
	// mod_limiter[len + 1] = 0;
	len = len + 2;//0까지
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(mod_limiter, line, len) == 0 || line == 0 || *line == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	free(mod_limiter);
	printf("gere_doc_help2 finished\n");
	// free(line);
}

void	here_doc_help(t_list *list)
{
	char	*string;
	char	*limiter;
	char	*fname;
	int		fd;

	limiter = (char *)(list->next->content);
	fname = get_filename();
	fd = open(fname, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	here_doc_help2(fd, limiter);
	free(list->next->content);
	list->next->content = fname;
}

int	heredoc(t_list *list)
{
	while (list)
	{
		if (list->content)
		{
			if (ft_strncmp((list->content), "<<", 3) == 0)
			{
				if (!(list->next) || !(list->next->content))
				{
					printf("syntax error near undexpected token \'newline\'");
					return (-1);
				}
				else
				{
					here_doc_help(list);
					// list = list->next->next;
					// continue;
					list = list->next;
					// return (1);
				}
			}
		}
		list = list->next;
	}
	return (0);
}

// heredoc : 파일 전부 일단 처음에 만들고
// 실행부에서는 알아서 limiter만 받고 하나씩 넣을 거긴 한데
// 그러면...
// 1. heredoc limiter 앞에서부터 하나씩 받기
// 2. heredoc limiter 마다 파일 생성해서 파일 이름 벡터에 넣기
// 3. 커맨드마다 heredoc으로 만들어진 파일 불러올건데... 문제는 같은 limiter 가 여러 개 있을 수 있다 -> key:value로는 해결이 불가능함.
// 4. 따라서? 


char *get_filename(void)
{
	char	*string;
	int		index;
	int		len;

	string = (char *)ft_calloc(10, sizeof(char));
	// ft_memmove(string, "/tmp/")
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
		// printf("%s\n", string);
	}
	return (string);
}


// 1. 들어온 string check;
// 2. 들어온 string 이 ~~~(126) 이면 ~~~\0으로 만들어 주기 (늘리기)
// 3. string[0]++;
// 4. index를 보며 만약 string[index] == 127 이면 string[index + 1]++.
// 5. string[index] < '0' 이면 string[index] = 0;

int	delete_local_file(t_list *list)
{
	while (list)
	{
		if (list->content)
		{
			if (ft_strncmp((list->content), "<<", 3) == 0)
			{
				if (!(list->next) || !(list->next->content))
				{
					printf("syntax error near undexpected token \'newline\'");
					return (-1);
				}
				else
				{
					unlink((char *)(list->next->content));
					// list = list->next->next;
					// continue;
					list = list->next;
					// return (1);
				}
			}
		}
		list = list->next;
	}
	return (0);
}


int main(void)
{
	t_list **list;

	// list = (t_list *)ft_calloc(1, sizeof(t_list *));
	ft_lstadd_back(list, ft_lstnew(ft_strdup("echo")));
	ft_lstadd_back(list, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(list, ft_lstnew(ft_strdup("limiter")));
	ft_lstadd_back(list, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(list, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(list, ft_lstnew(ft_strdup("limi")));

	t_list *temp;
	temp = *list;
	printf("stored : ");
	while (temp)
	{
		printf("%s ", ((char *)(temp->content)));
		temp = temp->next;
	}
	printf("\n");
	heredoc(*list);
	temp = *list;
	printf("modified : ");
	while (temp)
	{
		printf("%s ", ((char *)(temp->content)));
		temp = temp->next;
	}
	printf("\n");
	delete_local_file(*list);
	system("leaks a.out | grep leaked");
}


// gcc -g3 get_next_line/get_next_line.a -lreadline libft/libft.a heredoc.c