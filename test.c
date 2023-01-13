
#include "test.h"
int	command_run(t_list* list, char *line, char **envp);
void	child_process(t_list *list, char *line, char **envp, int fd[2][2]);

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

static int	builtin_check(char *line, t_list *node, t_copy *e)
{
	char *string = (char *)(node->content);

	if (ft_strncmp(string, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(string, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(string, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(string, "export", 7) == 0)
	{
		ft_export(line, node, e);
		return (4);
	}
	else if (ft_strncmp(string, "unset", 6) == 0)
	{
		ft_unset((char *)node->next->content, e);
		return (5);
	}
	else if (ft_strncmp(string, "env", 4) == 0)
	{
		ft_env(e);
		return (6);
	}
	else if (ft_strncmp(string, "exit", 5) == 0)
		return (7);
	return (0);
}

char *reading(void)
{
	char *line;
	line = 0;

	line = readline("./minishell >$");
	if (line && *line)
		add_history(line);
	return (line);
}

void exec(t_list *list, char *line, t_copy *e);


int main(int argc, char **argv, char **envp)
{

	char *line;
	t_list *list;
	t_copy env;

	line = 0;
	list = NULL;
	env.cp_envp = envp;

	while (1)
	{
		line = reading();
		list = parsing(line, envp);
		exec(list, line, &env);

	}
	argc = 0;
	argv = 0;
	envp = 0;
}

void	exec(t_list* list, char *line, t_copy *e)
{
	t_list *now;
	int flag;

	flag = 0;
	now = list->next;
	printf("exec\n");

	t_list *temp1;
	t_list *head;
	t_list *last;
	int temp_no;
	int	cmd_sign;

	last = 0;
	head = list->next;
	temp1 = head;
	while (temp1)
	{
		printf("%s ", (char *)(temp1->content));
		temp1 = temp1->next;
	}
	printf("\n");

	while (1)
	{
		temp_no = 0;
		cmd_sign = 0;
		temp1 = head;
		while (temp1)
		{
			if (temp1->content && ((char *)(temp1->content))[0] == '|')
			{
				temp_no = 1;
				last = temp1->next;
				break;
			}
			temp1 = temp1->next;
		}
		temp1 = head;
		while (temp1 && ((char *)(temp1->content))[0] != '|')
		{
			printf("%s ", temp1->content);
			temp1 = temp1->next;
		}
		printf("\n");
		temp1 = head;

		while (temp1 && ((char *)(temp1->content))[0] != '|')
		{
			if (sep_kind(temp1) && !(temp1->next))
			{
				printf("invalid syntax\n");
				break;
			}
			if (sep_kind(temp1) && sep_kind(temp1->next))
			{
				printf("syntax error near unexpected token '%s'\n", (char *)(temp1->next->content));
				break ;
			}
			if (sep_kind(temp1) == 1)
			{
				printf("infile : %s\n", (char *)(temp1->next->content));
			}
			else if (sep_kind(temp1) == 2)
			{
				printf("here_doc limiter : %s\n", (char *)(temp1->next->content));
			}
			else if (sep_kind(temp1) == 3)
			{
				printf("outfile : %s\n", (char *)(temp1->next->content));
			}
			else if (sep_kind(temp1) == 4)
			{
				printf("outfile_append : %s\n", (char *)(temp1->next->content));
			}
			else
			{
				// printf("command part : %s", (char *)(temp1->content))
				if (cmd_sign == 0)
				{
					if (flag == builtin_check(line, temp1, e))
					{
						printf("builtin : %s\n", (char *)(temp1->content));
					}
					else
						printf("command : %s\n", (char *)(temp1->content));
					cmd_sign = 1;
				}
				else
					printf("option : %s\n", (char *)(temp1->content));
				temp1 = temp1->next;
				continue;
			}
			temp1 = temp1->next->next;
		}
		printf("\n");

		if (temp1)
			head = last;
		else
			break;
	}


	//check done;




	command_run(list->next, line, e->cp_envp);

}

int	command_run(t_list* list, char *line, char **envp)
{
	int	pipefd[2][2];
	int pid = 0;
	//1. 다음 파이프 확인
	// 파이프 있으면 pipe
	// 없으면 그냥 가
	t_list *temp = list;


	pipefd[NEXT][READ] = 0;
	pipefd[NEXT][WRITE] = 0;
	while (temp)
	{
		
		//test print
		//test print
		t_list *temp2 = temp;
		printf(" running : ");
		while (temp && ft_strncmp(((char *)temp->content), "|", 2) != 0)
		{
			printf("%s ", (char *)temp->content);
			temp = temp->next;
		}
		printf("\n");
		temp = temp2;
		//test print done
		//test print done





		pipefd[PREV][READ] = pipefd[NEXT][READ];
		pipefd[PREV][WRITE] = 0;
		if (pipe_exists(temp))
			pipe(pipefd[NEXT]);
		else
		{
			// if (pipefd[PREV][READ])
			// {
			// 	close(pipefd[PREV][READ]);
			// 	pipefd[PREV][READ] = 0;
			// }
			// pipefd[NEXT][WRITE] = 1;
			pipefd[NEXT][WRITE] = 0;
			pipefd[NEXT][READ] = 0;
		}
		printf("%s : %d %d %d %d\n",(char *)temp->content, pipefd[0][1], pipefd[0][0], pipefd[1][1], pipefd[1][0]);



		pid = fork();
		if (pid == 0)
		{

			// printf("child process\n");
			// sleep(1);
			child_process(temp, line, envp, pipefd);
			exit (0);
		}
		else if (pid < 0)
		{
			// printf("fork failed\n");
			exit (1);
		}
		// printf("going parent\n");
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






	printf("#########parent started waiting##########\n");
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
	printf("exit with %d\n", status);
	if (status)
		perror("exit code");
	return (status);






}


void	child_process(t_list *list, char *line, char **envp, int fd[2][2])
{
	char **command = 0;
	t_list *temp = list;
	printf("child %s : %d %d %d %d\n",(char *)list->content, fd[0][1], fd[0][0], fd[1][1], fd[1][0]);
	// printf("%s $$\n", (char *)(temp->content));
	// printf("child got : ");
	// while (temp && ((char *)(temp->content))[0] != '|')
	// {
	// 	printf("%s ", (char *)(temp->content));
	// 	temp = temp->next;
	// }
	// printf("\n");

	// temp = list;
	while (temp && ((char *)(temp->content))[0] != '|')
	{
		// printf("current sep kind : %d\n", sep_kind(temp));
		if (sep_kind(temp) == 1)
		{
			fd[PREV][READ] = open((char *)temp->next->content, O_RDONLY, 0644);
		}
		else if (sep_kind(temp) == 2)
		{
			// printf("here_doc limiter : %s\n", (char *)(temp->next->content));
			printf("heredoc not implemented\n");
		}
		else if (sep_kind(temp) == 3)
		{
			fd[NEXT][WRITE] = open((char *)temp->next->content, O_RDWR | O_TRUNC | O_CREAT, 0644);
			// printf("outfile : %s\n", (char *)(temp->next->content));
		}
		else if (sep_kind(temp) == 4)
		{
			fd[NEXT][WRITE] = open((char *)temp->next->content, O_RDWR | O_APPEND | O_CREAT, 0644);
			// printf("outfile_append : %s\n", (char *)(temp->next->content));
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
	vector_print(command);



	// get path
	


	close(fd[NEXT][READ]);
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
		// return (perror("error on execve"), 1);
	perror("command not found");
	vector_free(command);
	exit(127);
}


