#include "main.h"

int main(int argc, char **argv, char **envp)
{
	char	*command[] = {"./exec_test", 0};
	// char *command[] = {"/usr/bin/awk", "{count++} END {print count}", 0};
	execve(command[0], command, envp);
	perror("ERROR ON EXECVE");
}

// awk access->path /bin/awk



// awk '{count++} END {print}'

// *command[] = {"/usr/bin/awk", "{count++} END {print}", 0}
// execve()

// awk '{fdjsalfd print}'