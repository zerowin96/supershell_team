
#include "test.h"

// typedef struct s_command
// {
// 	char	**command;
// 	int		priority;
	// no || or && : all 1s
	// if any of them available : rise from 1;
	// example : echo "123" && echo "456"
	// echo 123 : priority 0;
	// echo 456 : priority 1;
	// 아니, 아니지. 선후관계를 어떻게 하면 더 쉽게 파악할 수 있을까?

// }

// shapeof readline_family(prototype)
// {
// 	char *readline(const char *prompt);
// 	then : "prompt" on prompt;

// 	void rl_clear_history(void);
// 	then : clear history;

// 	rl_on_new_line
// 	rl_replace_line
// 	re_redisplay
// 	add_history


// }kkk
// 바보?????

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

static int	builtin_check(t_list *node, t_copy *e)
{
	char *string = (char *)(node->content);

	if (ft_strncmp(string, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(string, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(string, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(string, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(string, "unset", 6) == 0)
	{
		ft_unset((char *)node->next->content, e);
		return (1);
	}
	else if (ft_strncmp(string, "env", 4) == 0)
	{
		ft_env(e);
		return (1);
	}
	else if (ft_strncmp(string, "exit", 5) == 0)
		return (1);
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

void exec(t_list *list, t_copy *e);
// {
// 	t_list *now;

// 	now = list -> next;
// 	printf("exec\n");
// }

int main(int argc, char **argv, char **envp)
{
	// char *test[] = {"/bin/echo", "abcd", "efgh", 0};
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
		exec(list, &env);
		// readline () line 값을 parsing()
		// parsing () parsing 값을 char **에 담아
		// exec() char **을 실행시켜 (bulitin 유무 확인) 없으면 (< << > >>) 확인 exec 실행 (pipex)
		// 

		// cd 

		// if (line)
		// {
		// 	free(line);
		// 	line = (char *)NULL;
		// }
		// line = readline("enter a line :");
		// printf("line i got : |%s|\n", line);
		// if (line && *line)
		// 	add_history(line); 
		// rl_on_new_line();
		// perror();
	}
	argc = 0;
	argv = 0;
	envp = 0;
	// system("leaks a.out");
	// rl_clear_history();
	// execve(test[0], test, envp);
}

void	exec(t_list* list, t_copy *e)
{
	t_list *now;

	

	now = list->next;
	printf("exec\n");

	
	// infile 이 있는 경우 : pipe에서 들어온 입력을 무시함
		// ex) $echo 321785 | cat -e < infile1
	// outfile이 있는 경우 : pipe가 아닌 outfile에 출력함
		// ex) $cat -e < infile1 > outfile1 | cat -e
	// outfile2
		// ex) $cat -e < infile1 | cat -e > outfile1 | cat -e > outfile2
	// cat -e는 Ctrl-D가 들어올 때까지 계속되는 듯 :: cat이 알아서 할 것
	// limiter 가 다중으로 있을 경우 순서대로 적용
		// ex) cat -e << lim1 << lim2
		// lim2 / lim1 로 끝나지 않고 lim2 적용해야 끝남
		// lim1 이후부터의 here_doc 값이 출력됨 : **가장 마지막 here_doc만 받는다**
	
	// 전략 : 명령어는 다음 파이프 도달하기 전 까지만 보자
	// 부모는 앞에서부터 하나씩 읽으면서 파이프에 마주칠 때 마다 명령어 실행 준비
	// 1. 다음 파이프 있는지 확인 (파이프를 만들지 말지 결정)
	// 2-1. 파이프가 없다
		// 1. 파이프가 없으므로 infile outfile 만 신경쓰면 된다
		// 2. fd 이어주고 execve;
	// 2-2. 파이프가 있다
		// 1. 파이프가 있지만 infile outfile 신경쓴다.
		// 2. infile 이 있을 경우 이전 pipe를 읽지 않고 닫는다. infile을 연결한다.
		// 3. outfile이 있을 경우 새로운 pipe에 쓰지 않고 닫는다. outfile을 연결한다.
		// 4. fd 이어주고 execve;
	// 3. 부모는 waitpid 하면서 signal 확인(?) **wait 하면서 signal 들어오면 프로세스 죽여야 하나?**
	// 그런데, cd .. | ls 는 현재 폴더의 ls를 반환. cd ..이 무시됨
	// cd .. | ls | touch 123 해도 아무데도 123 파일이 생기지 않는다
	

	// while (list)
	// {
	// 	check if next pipe sign exists
	// 	{
	// 		generate pipe
	// 	}
	// 	not exist
	// 	{
	// 		nothing special
	// 	}
	// 	control fd : previous pipe

	// 	fork
	// 	child :
	// 	{
	// 		while next pipe or NULL
	// 		{
	// 			generate pipe
	// 			if current node is < or <<
	// 			{
	// 				check next node
	// 				open infile or here_doc
	// 				close read side of new pipe
	// 			}
	// 			if current node is > or >>
	// 			{
	// 				check next node
	// 				open outfile
	// 				close write side of new pipe
	// 			}
	// 		}
	// 		(only lefts command part)
	// 		run command.(check command, fd control and execve)
	// 	}
	// 	parent :
	// 	{
	// 		control fd : close pipes
	// 	}
	// }
	// while (1)
	// {
	// 	temp = waitpid(-1, &temp_code, 0); // 아무 자식프로세스나 종료되기를 기다림
	// 	if temp == last_pid // 맨 마지막 프로세스가 종료된 경우
	// 		exit_code = temp_code >> 8; // 맨 마지막 프로세스의 exit code 반환
	// 	if temp == -1 // 남은 자식 프로세스가 없는 경우
	// 		break ; // 끝
	// }
	// // exit_code 는 계속 가지고 있으면 된다.


	// finding command part : test

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
					if (builtin_check(temp1, e))
						printf("builtin : %s\n", (char *)(temp1->content));
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


}



