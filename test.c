
#include "test.h"
int		command_run(t_list* list, char *line, t_copy *e);
void	child_process(t_list *list, char *line, t_copy *e, int fd[2][2]);

# define READ 0
# define WRITE 1
# define PREV 0
# define NEXT 1

void	free_list(t_list *list)
{
	t_list *temp;

	while (list)
	{
		temp = list->next;
		if (list->content)
		{
			free(list->content);
			list->content = 0;
		}
		free(list);
		list = temp;
	}
}

int	check_access_h(char *name, char *path, int permission)
{
	char	*temp;
	char	*temp2;
	int		index;

	temp2 = 0;
	temp = 0;
	index = 0;
	if (name == 0)
		return (0);
	if (path != 0)
	{
		temp2 = ft_strjoin(path, "/");
		temp = ft_strjoin(temp2, name);
		free(temp2);
	}
	if (path == 0)
		temp = name;
	if (access(temp, permission) == 0)
		index = 1;
	if (path != 0)
	{
		free(temp);
		temp = 0;
	}
	return (index);
}

int	check_access(char *name, char **paths, int permission)
{
	int	index;

	index = 0;
	while (paths[index])
	{
		if (check_access_h(name, paths[index], permission))
			return (index + 2);
		index++;
	}
	if (check_access_h(name, 0, permission))
	{
		if (name[0] == '.' && name[1] == '/')
			return (1);
		else if (name[0] == '/')
			return (1);
	}
	return (-1);
}

char	**get_path_split(char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			break ;
		index++;
	}
	if (envp[index] == 0)
		return (0);
	return (ft_split(&envp[index][5], ':'));
}

char *string_connect(char *dst, char *src)
{
	int len1;
	int len2;
	char *temp;

	len1 = 0;
	len2 = 0;
	if (dst)
		len1 = ft_strlen(dst);
	if (src)
		len2 = ft_strlen(src);
	temp = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (len1)
		ft_memmove(temp, dst, len1);
	if (len2)
		ft_memmove(&temp[len1], src, len2);
	if (dst)
		free(dst);
	return (temp);
}

int pipe_exists(t_list *line)
{
	t_list *temp;
	temp = line;
	while (temp)
	{
		if (ft_strncmp(((char *)temp->content), "|", 2) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

// typedef struct s_com
// {
// 	t_list			*command;
// 	t_list			*infile;
// 	t_list			*heredoc;
// 	t_list			*outfile;
// 	t_list			*outfile_append;
// 	struct s_com	*next;
// }	t_com;

static int	sep_kind(t_list *node)
{
	if (ft_strncmp(node->content, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(node->content, "<<", 3) == 0)
		return (2);
	else if (ft_strncmp(node->content, ">", 2) == 0)
		return (3);
	else if (ft_strncmp(node->content, ">>", 3) == 0)
		return (4);
	else if (ft_strncmp(node->content, "|", 2) == 0)
		return (5);
	return (0);
}


static int	builtin_check(char *line, t_list *node, t_copy *e, char *string)
{
	// char *string = (char *)(node->content);

	if (ft_strncmp(string, "echo\0", 5) == 0)
		return (1);
	else if (ft_strncmp(string, "cd\0", 3) == 0)
		return (2);
	else if (ft_strncmp(string, "pwd\0", 4) == 0)
		return (3);
	else if (ft_strncmp(string, "export\0", 7) == 0)
		return (4);
	else if (ft_strncmp(string, "unset\0", 6) == 0)
		return (5);
	else if (ft_strncmp(string, "env\0", 4) == 0)
		return (6);
	else if (ft_strncmp(string, "exit\0", 5) == 0)
		return (7);
	return (0);
}

char *reading(void)
{
	char *line;

	printf("reading phase\n");
	line = readline("minishell-1.0$ ");
	if (line == 0)
	{
		rl_replace_line("", 1);
		write(2, "exit\n", 5);
		exit (0);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

int		builtin_exec(char *line, t_list *node, t_copy *e, int index)
{
	char	*temp_string = 0;
	t_list *temp = node;

	free_space(node);
	int result = 0;
	if (index == 1)
		ft_echo(line, e);
	else if (index == 2)
	{
		//이 부분 cd 안에 넣기
		if (node->next)
		{
			if (node->next->next != 0)
			{
				// perror("Too many argumet");
				ft_putstr_fd("too many arguments\n", 2);
				return (1);
			}
			ft_cd((char *)node->next->content, e);
		}
		else
			ft_cd(NULL, e);
	}
	else if (index == 3)
		ft_pwd();
	else if (index == 4)
		ft_export(line, e);
	else if (index == 5)
		ft_unset(line, e);
	else if (index == 6)
		ft_env(e);
	else if (index == 7)
		ft_exit();
	return (result);
	// update required : store exit code of result of executed builtin into variable "result"
}

int	command_check(t_list *list)
{
	t_list *temp1;

	temp1 = list->next;
	while (temp1)
	{
		if ((sep_kind(temp1) && !(temp1->next)))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (258);
		}
		else if ((sep_kind(temp1) && sep_kind(temp1->next)) || \
		(sep_kind(temp1) && (((char *)(temp1->next->content))[0] == ' ') \
		&& sep_kind(temp1->next->next)))
		{
			printf("syntax error near unexpected token '%s'\n", (char *)(temp1->next->content));
			return (258);
		}
		else if (sep_kind(temp1) == 0)
		{
			temp1 = temp1->next;
			continue;
		}
		temp1 = temp1->next->next;
	}
	return (0);
}

int	exec(t_list* list, char *line, t_copy *e)
{
	return (command_run(list->next, line, e));
}

int	status_return(int pid)
{
	int index = 0;
	int ret_status = 0;
	int status = 0;
	int temp_pid;
	temp_pid = 1;
	while (temp_pid >= 0)
	{
		temp_pid = waitpid(-1, &status, 0);
		if (temp_pid == pid)
			ret_status = status >> 8;
		if (temp_pid < 0)
			break;
	}
	return (ret_status);
}

int	command_run(t_list* list, char *line, t_copy *e)
{
	int	pipefd[2][2];
	int pid = 0;
	t_list *temp;

	temp = list;
	pipefd[NEXT][READ] = 0;
	pipefd[NEXT][WRITE] = 0;
	while (temp)
	{
		//sep
		pipefd[PREV][READ] = pipefd[NEXT][READ];
		pipefd[PREV][WRITE] = 0;
		if (pipe_exists(temp))
			pipe(pipefd[NEXT]);
		else
		{
			pipefd[NEXT][WRITE] = 0;
			pipefd[NEXT][READ] = 0;
		}
		//sep
		pid = fork();
		if (pid == 0)
		{
			child_process(temp, line, e, pipefd);
			exit (127);
		}
		else if (pid < 0)
		{
			perror("fork failed");
			exit (1);
		}
		//sep
		if (pipefd[PREV][READ])
		{
			close(pipefd[PREV][READ]);
			pipefd[PREV][READ] = 0;
		}
		if (pipefd[NEXT][WRITE])
		{
			close(pipefd[NEXT][WRITE]);
			pipefd[NEXT][WRITE] = 0;
		}
		//sep
		while (temp && ft_strncmp(((char *)temp->content), "|", 2) != 0)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
	return (status_return(pid));
}

void	command_split_delspace(t_list *list, char **temp_string)
{
	while (1)
	{
		int len = ft_strlen((*temp_string));
		if (len == 0)
			break ;
		if ((*temp_string)[len - 1] == ' ')
			(*temp_string)[len - 1] = 0;
		else
			break ;
	}
}

int	command_split(t_list *temp, int (*fd)[2], char ***command, char **temp_string)
{
	int sep;

	while (temp && ((char *)(temp->content))[0] != '|')
	{
		if (((char *)(temp->content))[0] == ' ')
		{
			temp = temp->next;
			if ((*command))
				(*temp_string) = string_connect((*temp_string), " ");
			continue;
		}
		sep = sep_kind(temp);
		if (sep == 1 || sep == 2)
		{
			fd[PREV][READ] = open(((char *)(temp->next->content)), O_RDONLY);
			if (fd[PREV][READ] < 0)
			{
				if (sep == 1)
					perror("file not found");
				else
					perror("heredoc temp file error");
				return (1);
			}
		}
		else if (sep == 3 || sep == 4)
		{
			if (sep == 3)
				fd[NEXT][WRITE] = open(((char *)(temp->next->content)), O_RDWR | O_TRUNC | O_CREAT, 0644);
			else
				fd[NEXT][WRITE] = open(((char *)(temp->next->content)), O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd[NEXT][WRITE] < 0)
			{
				perror("file open error");
				exit(1);
			}
		}
		else
		{
			(*command) = vector_add((*command), (char *)(temp->content));
			(*temp_string) = string_connect((*temp_string), temp->content);
			temp = temp->next;
			continue;
		}
		temp = temp->next->next;
	}
	command_split_delspace(temp, temp_string);
	return (0);
}


void	child_process(t_list *list, char *line, t_copy *e, int fd[2][2])
{
	t_list *temp = list;
	char **envp = e->cp_envp;

	char **command = 0;
	char *temp_string = 0;

	int tnum;
	tnum = command_split(list, fd, &command, &temp_string);
	if (tnum)
		exit (tnum);

	if (fd[PREV][READ])
	{
		dup2(fd[PREV][READ], 0);
		close(fd[PREV][READ]);
	}
	if (fd[NEXT][WRITE])
	{
		dup2(fd[NEXT][WRITE], 1);
		close(fd[NEXT][WRITE]);
	}
	if (fd[NEXT][READ])
		close(fd[NEXT][READ]);

	if (builtin_check(temp_string, list, e, command[0]))
	{
		int result = builtin_exec(temp_string, list, e, builtin_check(temp_string, list, e, command[0]));
		free(temp_string);
		exit (result);
	}

	free(temp_string);
	free_space(list);

	int path_index = 0;
	char **paths = get_path_split(envp);
	int errcheck = 0;

	path_index = check_access(command[0], paths, X_OK);
	if (path_index == 1)
		errcheck = execve(command[0], command, envp);
	else if (path_index > 1)
		errcheck = execve(ft_strjoin(paths[path_index - 2], ft_strjoin("/", command[0])), command, envp);
	if (errcheck < 0)
	{
		perror("error on execve");
		exit (1);
	}
	perror("command not found");
	vector_free(command);
	exit(127);
}

int	quote_check(t_list *list)
{
	int	len;

	while (list->next)
		list = list->next;
	len = ft_strlen((char *)(list->content));
	if (((char *)(list->content))[0] == '\'')
	{
		if (((char *)(list->content))[len - 1] != '\'' || len == 1)
			printf("minishell: quote not closed: close quote to make commands run\n");
		else
			return (0);
	}
	else if (((char *)(list->content))[0] == '\"')
	{
		if (((char *)(list->content))[len - 1] != '\"' || len == 1)
			printf("minishell: quote not closed: close quote to make commands run\n");
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	int i;
	int j;
	char *line;
	t_list *list;
	t_copy env;
	int result = 0;

	line = 0;
	list = NULL;
	i = 0;
	env.cp_envp = envp;
	env.onlyenv = 0;
	while (envp[i])
	{
		env.onlyenv = vector_add(env.onlyenv, envp[i]);
		i++;
	}

	while (1)
	{
		line = reading();
		if (line == 0 || *line == 0)
			continue;
		list = first_parsing(line, env.cp_envp, result);
		if (list == 0)
			continue;
		if (command_check(list))
		{
			result = 258;
			free(line);
			free_list(list);
			continue;
		}
		heredoc(list->next);
		if (pipe_exists(list->next) == 0 && builtin_check(line, list->next, &env, list->next->content))
		{
			char **command = 0;
			char *temp_string = 0;
			int fd[3][2];
			int	temp_fd[2];
			t_list *temp;
			temp = list->next;

			fd[0][0] = 0;
			fd[0][1] = 0;
			fd[1][0] = 0;
			fd[1][1] = 0;
			fd[2][0] = dup(0);
			fd[2][1] = dup(1);


			int tnum;
			tnum = command_split(list->next, fd, &command, &temp_string);
			if (tnum)
			{
				result = tnum;
				
			}
			if (fd[PREV][READ])
			{
				dup2(fd[PREV][READ], 0);
				close(fd[PREV][READ]);
			}
			if (fd[NEXT][WRITE])
			{
				dup2(fd[NEXT][WRITE], 1);
				close(fd[NEXT][WRITE]);
			}

			result = builtin_exec(temp_string, list->next, &env, builtin_check(temp_string, list->next, &env, list->next->content));
			if (command)
				vector_free(command);
			if (temp_string)
				free(temp_string);
			
			dup2(fd[2][0], 0);
			dup2(fd[2][1], 1);
			close(fd[2][0]);
			close(fd[2][1]);
		}
		else
			result = exec(list, line, &env);
		delete_local_file(list->next);
		free(line);
		free_list(list);
	}
}
