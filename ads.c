#include "test.h"

int main(int argc, char **argv, char **envp)
{
	char *command[] = {"/bin/cat", ""a"a", "b" ,"c"c"", 0};
	int fd = open("outfile2", O_RDWR | O_TRUNC);
	dup2(fd, 1);
	execve(command[0], command, envp);
	return (0);
}