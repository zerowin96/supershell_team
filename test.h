
#ifndef TEST_H
# define TEST_H
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

t_list *parsing(char *line);

typedef struct s_cnt
{
	int pipe_cnt;
	char **order;
	int q_flag;
} t_cnt;

#endif
