
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

typedef struct s_cnt
{
	int pipe_cnt;
	char **order;
	int q_flag;
} t_cnt;

typedef struct s_copy
{
	char **cp_envp;
} t_copy;

t_list *parsing(char *line, char **envp);
void ft_unset(char *temp, t_copy *e);
void ft_env(t_copy *e);



#endif
