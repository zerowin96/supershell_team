#include "test.h"

int main(int argc, char **argv, char **envp)
{
	// char *cmd1[] = {"ls", "./pipex", ".", "-al", 0};
	//	-al을 폴더이름 옵션으로 받는다. 

	// execve(cmd1[0], cmd1, envp);

	execve(argv[1], &argv[1], envp); //경로는 whereis 로 알아서 찾아서 넣으시오
	perror("run failed");
}