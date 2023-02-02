#include "test.h"

char	*get_filename(void);
void	temp_list_print(t_list *list);

int	here_doc_help2_child(char *limiter, int fd)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter) + 1;
	heredoc_handle_signal();
	while (1)
	{
		line = readline("> ");
		if (line == 0)
			break ;
		else if (ft_strncmp(limiter, line, len) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit (0);
}

int	here_doc_help2(int fd, char *limiter)
{
	int		len;
	int		pid;
	int		status;

	pid = fork();
	len = ft_strlen(limiter) + 1;
	if (pid == 0)
		here_doc_help2_child(limiter, fd);
	else
	{
		parent_handle_signal();
		waitpid(pid, &status, 0);
		if (status >> 8)
			return (status >> 8);
	}
	return (0);
}

int	here_doc_help(t_list *list)
{
	char	*limiter;
	char	*fname;
	int		fd;
	int		sign;

	limiter = ft_strdup((char *)(list->next->content));
	fname = get_filename();
	fd = open(fname, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	sign = here_doc_help2(fd, limiter);
	close(fd);
	free(limiter);
	free(list->next->content);
	list->next->content = ft_strdup("0");
	if (sign)
	{
		unlink(fname);
		free(fname);
		return (sign);
	}
	free(list->next->content);
	// free(fname);
	list->next->content = fname;
	return (0);
}

int	heredoc(t_list *list)
{
	t_list	*head;

	head = list;
	while (list)
	{
		if (list->content)
		{
			if (ft_strncmp((list->content), "<<", 3) == 0)
			{
				if (((char *)(list->next->content))[0] == ' ')
					list = list->next;
				if (!(list->next) || !(list->next->content))
				{
					printf("syntax error near undexpected token \'newline\'");
					return (-1);
				}
				if (here_doc_help(list))
					return (delete_local_file(head), 1);
			}
		}
		list = list->next;
	}
	return (0);
}

char	*get_filename(void)
{
	char	*string;
	int		index;
	int		len;

	string = (char *)ft_calloc(17, sizeof(char));
	ft_memmove(string, "100000000000.tmp", 16);
	while (access(string, F_OK) == 0)
	{
		index = -1;
		string[0]++;
		len = ft_strlen(string);
		while (++index < len)
		{
			if (string[index] == 127)
			{
				string[index] = '0';
				string[index + 1]++;
				if (index + 1 == len)
					len++;
			}
			if (string[index] < '0' && string[index] != '.')
				string[index] = '0';
		}
	}
	return (string);
}

int	delete_local_file(t_list *list)
{
	while (list)
	{
		if (list->content)
		{
			if (ft_strncmp((list->content), "<<", 3) == 0)
			{
				if (((char *)(list->next->content))[0] == ' ')
					list = list->next;
				if (!(list->next) || !(list->next->content))
				{
					printf("syntax error near undexpected token \'newline\'");
					return (-1);
				}
				else if (ft_strncmp(list->next->content, "0", 2) == 0)
					return (-1);
				else
					unlink((char *)(list->next->content));
			}
		}
		list = list->next;
	}
	return (0);
}

// void	temp_list_print(t_list *list)
// {
// 	if (!(list->content))
// 		list = list->next;
// 	while (list)
// 	{
// 		printf("%s ", list->content);
// 		list = list->next;
// 	}
// 	printf("\n");
// }