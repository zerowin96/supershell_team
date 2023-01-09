
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

char *reading(void)
{
	char *line;
	line = 0;

	line = readline("./minishell >$");
	if (line && *line)
		add_history(line);
	return (line);
}

void exec(t_list *list);
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

	line = 0;
	list = NULL;
	while (1)
	{
		line = reading();


		list = parsing(line, envp);
		exec(list);
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
	system("leaks a.out");
	// rl_clear_history();
	// execve(test[0], test, envp);
}

void	exec(t_list* list)
{
	t_list *now;

	now = list -> next;
	printf("exec\n");

	// infile 이 있는 경우 : pipe에서 들어온 입력을 무시함
		// ex) $echo 321785 | cat -e < infile1
	// outfile이 있는 경우 : pipe가 아닌 outfile에 출력함
		// ex) $cat -e < infile1 > outfile1 | cat -e
	// cat -e는 Ctrl-D가 들어올 때까지 계속되는 듯 :: cat이 알아서 할 것
	// limiter 가 다중으로 있을 경우 순서대로 적용
		// ex) cat -e << lim1 << lim2
		// lim2 / lim1 로 끝나지 않고 lim2 적용해야 끝남
		// lim1 이후부터의 here_doc 값이 출력됨 : 가장 마지막 here_doc만 받는다.
	
}