
#include "test.h"
int		command_run(t_list* list, char *line, t_copy *e);
void	child_process(t_list *list, char *line, t_copy *e, int fd[2][2]);

# define READ 0
# define WRITE 1
# define PREV 0
# define NEXT 1

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
	{
		len1 = ft_strlen(dst);
	}
	if (src)
	{
		len2 =  ft_strlen(src);
	}
	
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

typedef struct s_com
{
	t_list			*command;
	t_list			*infile;
	t_list			*heredoc;
	t_list			*outfile;
	t_list			*outfile_append;
	struct s_com	*next;
}	t_com;

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

// static int	builtin_check(char *line, t_list *node, t_copy *e)
// static int	builtin_check(char *line, t_list *node, t_copy *e, char *string)
// {
// 	// char *string = (char *)(node->content);

// 	if (ft_strncmp(string, "echo\0", 5) == 0)
// 	{
// 		ft_echo(line, e);
// 		return (1);
// 	}
// 	else if (ft_strncmp(string, "cd\0", 3) == 0)
// 	{
// 		if (node->next)
// 		{
// 			if (node->next->next != 0)
// 			{
// 				perror("Too many argumet\n");
// 				return (1);
// 			}
// 			ft_cd((char *)node->next->content, e);
// 		}
// 		else
// 			ft_cd(NULL, e);
// 		return (1);
// 	}
// 	else if (ft_strncmp(string, "pwd\0", 4) == 0)
// 	{
// 		ft_pwd();
// 		return (1);
// 	}
// 	else if (ft_strncmp(string, "export\0", 7) == 0)
// 	{
// 		ft_export(line, e);
// 		return (1);
// 	}
// 	else if (ft_strncmp(string, "unset\0", 6) == 0)
// 	{
// 		ft_unset(line, e);
// 		return (1);
// 	}
// 	else if (ft_strncmp(string, "env\0", 4) == 0)
// 	{
// 		ft_env(e);
// 		return (1);
// 	}
// 	else if (ft_strncmp(string, "exit\0", 5) == 0)
// 	{
// 		ft_exit();
// 	}
// 	return (0);
// }

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
	line = 0;

	line = readline("minishell-1.0$ ");
	if (line == 0)
	{
		write(2, "\nexit\n", 7);
		exit (0);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

int		builtin_exec(char *line, t_list *node, t_copy *e, int index)
{
	//put lines into one character string;
	// char *string;
	// string = 
	char	*temp_string = 0;
	t_list *temp = node;
	// printf("builtin_exec input node[0] : %s\n", (char *)(node->content));
	// while (temp && temp->content && ((char *)(temp->content))[0] != '|')
	// {
	// 	temp_string = string_connect(temp_string, temp->content);
	// 	//library function
	// 	// strcat(temp_string, temp->content);
	// 	//library function
	// 	temp = temp->next;
	// 	if (temp && temp->content && ((char *)(temp->content))[0] != '|')
	// 		temp_string = string_connect(temp_string, " ");
	// }
	// printf("temp_string : %s\n", temp_string);


















	free_space(node);
	int result = 0;
	if (index == 1)
		ft_echo(line, e);
	else if (index == 2)
	{
		if (node->next)
		{
			if (node->next->next != 0)
			{
				perror("Too many argumet\n");
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
	// free (string);
	return (result);
	// update required : store exit code of result of executed builtin into variable "result"
}

// void exec(t_list *list, char *line, t_copy *e);


int	exec(t_list* list, char *line, t_copy *e)
{
	t_list *now;
	int flag;
	char **envp = e->cp_envp;
	flag = 0;
	now = list->next;


	t_list *temp1;
	t_list *head;
	t_list *last;

	int	cmd_sign;

	last = 0;
	head = list->next;
	temp1 = head;


	while (1)
	{
		// temp_no = 0;
		cmd_sign = 0;
		temp1 = head;
		while (temp1)
		{
			if (temp1->content && ((char *)(temp1->content))[0] == '|')
			{
				last = temp1->next;
				break;
			}
			temp1 = temp1->next;
		}
		temp1 = head;

		while (temp1 && ((char *)(temp1->content))[0] != '|')
		{
			if (sep_kind(temp1) && (!(temp1->next) || \
			(((char *)(temp1->next->content))[0] == ' ') && !(temp1->next->next)))
			{
				printf("invalid syntax\n");
				return -11;
			}
			if (sep_kind(temp1) && sep_kind(temp1->next))
			{
				printf("syntax error near unexpected token '%s'\n", (char *)(temp1->next->content));
				return -11;
			}
			if (sep_kind(temp1) == 0)
			{
				temp1 = temp1->next;
				continue;
			}
			temp1 = temp1->next->next;
		}
		if (temp1)
			head = last;
		else
			break;
	}
	return (command_run(list->next, line, e));
}




int	command_run(t_list* list, char *line, t_copy *e)
{
	int	pipefd[2][2];
	int pid = 0;
	char **envp = e->cp_envp;
	t_list *temp = list;


	pipefd[NEXT][READ] = 0;
	pipefd[NEXT][WRITE] = 0;
	while (temp)
	{
		// t_list *temp2 = temp;
		// temp = temp2;




		pipefd[PREV][READ] = pipefd[NEXT][READ];
		pipefd[PREV][WRITE] = 0;
		if (pipe_exists(temp))
			pipe(pipefd[NEXT]);
		else
		{
			pipefd[NEXT][WRITE] = 0;
			pipefd[NEXT][READ] = 0;
		}

		pid = fork();
		if (pid == 0)
		{
			child_process(temp, line, e, pipefd);
			exit (0);
		}
		else if (pid < 0)
		{
			exit (1);
		}




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



		while (temp && ft_strncmp(((char *)temp->content), "|", 2) != 0)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}

	// printf("#########parent started waiting##########\n");
	int index = 0;
	int ret_status = 0;
	int status = 0;
	int temp_pid = 0;
	temp_pid = 1;
	while (temp_pid >= 0)
	{
		temp_pid = waitpid(-1, &status, 0);
		if (temp_pid == pid)
			ret_status = status >> 8;
		if (temp_pid < 0)
			break;
	}
	// printf("exit with %d\n", status);
	// if (status)
	// 	perror("exit code");
	return (ret_status);






}


void	command_split(t_list *temp, int (*fd)[2], char ***command, char **temp_string)
{
	// char *(*temp_string) = 0;
	// char **(*command) = 0;

	while (temp && ((char *)(temp->content))[0] != '|')
	{
		// printf("current sep kind : %d\n", sep_kind(temp));
		if (((char *)(temp->content))[0] == ' ')
		{
			temp = temp->next;
			if ((*command))
			{
				printf("(space)");
				(*temp_string) = string_connect((*temp_string), " ");
			}
			continue;
		}
		if (sep_kind(temp) == 1)
		{
			if (((char *)(temp->next->content))[0] == ' ')
				temp = temp->next;
			fd[PREV][READ] = open(((char *)(temp->next->content)), O_RDONLY);
			if (fd[PREV][READ] < 0)
			{
				perror("file not found");
				exit(1);
			}
		}
		else if (sep_kind(temp) == 2)
		{
			if (((char *)(temp->next->content))[0] == ' ')
				temp = temp->next;
			// printf("here_doc limiter : %s\n", ((char *)((temp->next->content))));
			printf("heredoc not implemented\n");
			exit(1);
		}
		else if (sep_kind(temp) == 3)
		{
			printf("(OUTFILE OPEN  TRUNC)");
			if (((char *)(temp->next->content))[0] == ' ')
				temp = temp->next;
			fd[NEXT][WRITE] = open(((char *)(temp->next->content)), O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd[NEXT][WRITE] < 0)
			{
				perror("file not found");
				exit(1);
			}
			// printf("outfile : %s\n", ((char *)((temp->next->content))));
		}
		else if (sep_kind(temp) == 4)
		{
			printf("(OUTFILE OPEN APPEND)");
			if (((char *)(temp->next->content))[0] == ' ')
				temp = temp->next;
			fd[NEXT][WRITE] = open(((char *)(temp->next->content)), O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd[NEXT][WRITE] < 0)
			{
				perror("file not found");
				exit(1);
			}
			// printf("outfile_append : %s\n", ((char *)((temp->next->content))));
		}
		else
		{
			(*command) = vector_add((*command), (char *)(temp->content));
			printf("%s", temp->content);
			(*temp_string) = string_connect((*temp_string), temp->content);
			// printf("command part : %s\n", (char *)(temp->content));
			temp = temp->next;
			continue;
		}
		temp = temp->next->next;
	}
	// vector_print(command);
	printf("\n");

	// printf("pre__temp_string : %s$\n", (*temp_string));
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
	// printf("post_temp_string : %s$\n", (*temp_string));

	// return (command);
}
























void	child_process(t_list *list, char *line, t_copy *e, int fd[2][2])
{
	t_list *temp = list;
	char **envp = e->cp_envp;


	char **command = 0;
	char *temp_string = 0;
	command_split(list, fd, &command, &temp_string);


	if (fd[PREV][READ])
	{
		dup2(fd[PREV][READ], 0);
		close(fd[PREV][READ]);
	}
	if (fd[NEXT][WRITE])
	{
		dup2(fd[NEXT][WRITE], 1);
		close(fd[NEXT][WRITE]);
		// close(fd[NEXT][READ]);
	}
	if (fd[NEXT][READ])
		close(fd[NEXT][READ]);




	// quote_trim(list);
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
	write(2, "path_index is : ", 17);
	ft_putnbr_fd(path_index, 2);
	write(2, "\n", 1);
	if (path_index == 1)
		errcheck = execve(command[0], command, envp);
	else if (path_index > 1)
		errcheck = execve(ft_strjoin(paths[path_index - 2], ft_strjoin("/", command[0])), command, envp);
	write(2, "not executed : ", 16);
	if (errcheck < 0)
	{
		perror("error on execve");
		exit (1);
	}
	write(2, "Command not found\n", 19);
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
		list = first_parsing(line, env.onlyenv, result);//, result);
		if (list == 0)
			continue;
		// if (quote_check(list->next))
		// 	continue;
		if (pipe_exists(list->next) == 0 && builtin_check(line, list->next, &env, list->next->content))
		{
			char **command = 0;
			char *temp_string = 0;
			int fd[2][2];
			int	temp_fd[2];
			t_list *temp;
			temp = list->next;

			fd[0][0] = 0;
			fd[0][1] = 0;
			fd[1][0] = 0;
			fd[1][1] = 0;
			temp_fd[0] = 0;
			temp_fd[1] = 0;
			dup2(0, temp_fd[0]);
			dup2(1, temp_fd[1]);

			command_split(list->next, fd, &command, &temp_string);
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
			
			dup2(temp_fd[0], 0);
			dup2(temp_fd[1], 1);

			// $? 업데이트하기 (result 값)
		}
		else if (pipe_exists(list->next) == 0)
		{
			result = exec(list, line, &env);
			// $? 업데이트하기 (result 값)
		}
		else
		{
			result = exec(list, line, &env);
			// $? 업데이트하기 (result 값)
		}
	}
	argc = 0;
	argv = 0;
	envp = 0;
}
