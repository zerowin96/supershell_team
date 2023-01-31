#include "test.h"
// #include <unistd.h>
char *get_filename(void);

void	here_doc_help2(int fd, char *limiter)
{
	char	*line;
	char	*mod_limiter;
	int		len;

	len = ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (line == 0)
			break;
		else if (ft_strncmp(limiter, line, len) == 0)
		{
			free(line);
			break;
		}
		
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
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
				if (((char *)(list->next->content))[0] == ' ')
					list = list->next;
				if (!(list->next) || !(list->next->content))
				{
					printf("syntax error near undexpected token \'newline\'");
					return (-1);
				}
				else
					here_doc_help(list);
			}
		}
		list = list->next;
	}
	return (0);
}

char *get_filename(void)
{
	char	*string;
	int		index;
	int		len;

	string = (char *)ft_calloc(17, sizeof(char));
	ft_memmove(string, "100000000000.tmp", 16);
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
			if (string[index] < '0' && string[index] != '.')
				string[index] = '0';
			index++;
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
				else
					unlink((char *)(list->next->content));
			}
		}
		list = list->next;
	}
	return (0);
}
