#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

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

int main(int argc, char **argv, char **envp)
{
	char *test[] = {"/bin/echo", "abcd", "efgh", 0};
	char *line;

	line = 0;

	while(1)
	{
		// readline () line 값을 parsing()
		// parsing () parsing 값을 char **에 담아
		// exec() char **을 실행시켜 (bulitin 유무 확인) 없으면 (< << > >>) 확인 exec 실행 (pipex)
		// 

		// cd 

		if (line)
		{
			free(line);
			line = (char *)NULL;
		}
		line = readline("enter a line :");
		printf("line i got : |%s|\n", line);
		if (line && *line)
			add_history(line); // void
		
		
		// rl_on_new_line();
	}
	// rl_clear_history();
	// execve(test[0], test, envp);
}