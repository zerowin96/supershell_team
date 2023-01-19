
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
static int	builtin_check(char *line, t_list *node, t_copy *e, char *string)
{
	// char *string = (char *)(node->content);

	if (ft_strncmp(string, "echo\0", 5) == 0)
	{
		ft_echo(line, e);
		return (1);
	}
	else if (ft_strncmp(string, "cd\0", 3) == 0)
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
		return (1);
	}
	else if (ft_strncmp(string, "pwd\0", 4) == 0)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strncmp(string, "export\0", 7) == 0)
	{
		ft_export(line, e);
		return (1);
	}
	else if (ft_strncmp(string, "unset\0", 6) == 0)
	{
		ft_unset(line, e);
		return (1);
	}
	else if (ft_strncmp(string, "env\0", 4) == 0)
	{
		ft_env(e);
		return (1);
	}
	else if (ft_strncmp(string, "exit\0", 5) == 0)
	{
		ft_exit();
	}
	return (0);
}

char *reading(void)
{
	char *line;
	line = 0;

	line = readline("nanoshell MK.X enhanced remastered lib ver.1.16 broodwar << DOWNLOAD >> ");
	if (line && *line)
		add_history(line);
	return (line);
}

void exec(t_list *list, char *line, t_copy *e);


void	exec(t_list* list, char *line, t_copy *e)
{
	t_list *now;
	int flag;
	char **envp = e->cp_envp;
	flag = 0;
	now = list->next;
	// printf("exec\n");

	t_list *temp1;
	t_list *head;
	t_list *last;
	// int temp_no;
	int	cmd_sign;

	last = 0;
	head = list->next;
	temp1 = head;
	// while (temp1)
	// {
	// 	printf("%s ", (char *)(temp1->content));
	// 	temp1 = temp1->next;
	// }
	// printf("\n");

	while (1)
	{
		// temp_no = 0;
		cmd_sign = 0;
		temp1 = head;
		while (temp1)
		{
			if (temp1->content && ((char *)(temp1->content))[0] == '|')
			{
				// temp_no = 1;
				last = temp1->next;
				break;
			}
			temp1 = temp1->next;
		}
		// temp1 = head;
		// while (temp1 && ((char *)(temp1->content))[0] != '|')
		// {
		// 	printf("%s ", temp1->content);
		// 	temp1 = temp1->next;
		// }
		// printf("\n");
		temp1 = head;

		while (temp1 && ((char *)(temp1->content))[0] != '|')
		{


			if (sep_kind(temp1) && !(temp1->next))
			{
				printf("invalid syntax\n");
				break ;
			}
			if (sep_kind(temp1) && sep_kind(temp1->next))
			{
				printf("syntax error near unexpected token '%s'\n", (char *)(temp1->next->content));
				break ;
			}
			// if (sep_kind(temp1) == 1)
			// {
			// 	printf("infile : %s\n", (char *)(temp1->next->content));
			// }
			// else if (sep_kind(temp1) == 2)
			// {
			// 	printf("here_doc limiter : %s\n", (char *)(temp1->next->content));
			// }
			// else if (sep_kind(temp1) == 3)
			// {
			// 	printf("outfile : %s\n", (char *)(temp1->next->content));
			// }
			// else if (sep_kind(temp1) == 4)
			// {
			// 	printf("outfile_append : %s\n", (char *)(temp1->next->content));
			// }
			// else
			if (sep_kind(temp1) == 0)
			{
				// printf("command part : %s", (char *)(temp1->content))
				// if (cmd_sign == 0)
				// {
				// 	if (builtin_check(line, temp1, e) == 1)
				// 		printf("builtin : %s\n", (char *)(temp1->content));
				// 	else
				// 		printf("command : %s\n", (char *)(temp1->content));
				// 	cmd_sign = 1;
				// }
				// else
				// 	printf("option : %s\n", (char *)(temp1->content));
				temp1 = temp1->next;
				continue;
			}
			temp1 = temp1->next->next;
		}
		// printf("\n");

		if (temp1)
			head = last;
		else
			break;
	}


	//check done;




	command_run(list->next, line, e);

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
	return (status);






}


void	child_process(t_list *list, char *line, t_copy *e, int fd[2][2])
{
	char **command = 0;
	t_list *temp = list;
	char **envp = e->cp_envp;
	// printf("child %s : %d %d %d %d\n",(char *)list->content, fd[0][1], fd[0][0], fd[1][1], fd[1][0]);
	// printf("%s $$\n", (char *)(temp->content));
	// printf("child got : ");
	// while (temp && ((char *)(temp->content))[0] != '|')
	// {
	// 	printf("%s ", (char *)(temp->content));
	// 	temp = temp->next;
	// }
	// printf("\n");

	// temp = list;
	free_space(list);
	while (temp && ((char *)(temp->content))[0] != '|')
	{
		// printf("current sep kind : %d\n", sep_kind(temp));
		if (((char *)(temp->content))[0] == ' ')
		{
			temp = temp->next;
			continue;
		}
		if (sep_kind(temp) == 1)
		{
			fd[PREV][READ] = open(((char *)(temp->next->content)), O_RDONLY);
			if (fd[PREV][READ] < 0)
			{
				perror("file not found");
				exit(1);
			}
		}
		else if (sep_kind(temp) == 2)
		{
			// printf("here_doc limiter : %s\n", ((char *)((temp->next->content))));
			printf("heredoc not implemented\n");
			exit(1);
		}
		else if (sep_kind(temp) == 3)
		{
			fd[NEXT][WRITE] = open(((char *)(temp->next->content)), O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd[NEXT][NEXT] < 0)
			{
				perror("file not found");
				exit(1);
			}
			// printf("outfile : %s\n", ((char *)((temp->next->content))));
		}
		else if (sep_kind(temp) == 4)
		{
			fd[NEXT][WRITE] = open(((char *)(temp->next->content)), O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd[NEXT][NEXT] < 0)
			{
				perror("file not found");
				exit(1);
			}
			// printf("outfile_append : %s\n", ((char *)((temp->next->content))));
		}
		else
		{
			command = vector_add(command, (char *)(temp->content));
			// printf("command part : %s\n", (char *)(temp->content));
			temp = temp->next;
			continue;
		}
		temp = temp->next->next;
	}
	// vector_print(command);


	// get path
	


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




	// ft_putstr_fd("file_descriptor : ", 2);
	// ft_putnbr_fd(fd[PREV][WRITE],2);
	// ft_putstr_fd("  ", 2);
	// ft_putnbr_fd(fd[PREV][READ],2);
	// ft_putstr_fd("  ", 2);
	// ft_putnbr_fd(fd[NEXT][WRITE],2);
	// ft_putstr_fd("  ", 2);
	// ft_putnbr_fd(fd[NEXT][READ],2);
	// ft_putstr_fd("  done\n", 2);

	// quote_trim(list);
	if (builtin_check(line, list, e, command[0]))
		exit (0);
	write(2,"not built in :", 14);
	ft_putstr_fd(command[0], 2);
	write(2,"\n",1);
	free_space(list);
		//BUILTIN 의 실행 결과에 따라 exit의 인자 바꿔야 함.

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
		list = parsing(line, envp);
		if (list == 0)
			continue;
		// if (quote_check(list->next))
		// 	continue;
		if (pipe_exists(list->next) == 0 && builtin_check(line, list, &env, list->next->content))
		{
			//이거 근데 이렇게 하면 안 되고, << infile cat -e 처럼 명령어가 나중에 들어오는 경우 있으니까 명령어 찾아주는 것 부터 해야 함. 
			//이거는 다른 함수에 있는 거 독립시켜서 끌어오는 게 맞다.
			printf("builtin executed without forking\n");
			continue;
		}
		exec(list, line, &env);
	}
	argc = 0;
	argv = 0;
	envp = 0;
}
