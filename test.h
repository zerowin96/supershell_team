
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
	char **onlyenv;
} t_copy;


t_list *parsing(char *line, char **envp);
void ft_unset(char *line, t_copy *env);
void ft_env(t_copy *e);
void ft_export(char *line, t_copy *env);
char	**vector_add(char **vector, char *string);
void	vector_print(char **vector);
void	vector_replace(char **vector, int replace_index, char *replace_string);
char	**vector_delete_index(char **vector, int delete_index);
void	vector_free(char **vector);
int		string_compare(char *string, char *compare);
int		get_vector_len(char **vector);
void	env_expansion(t_list *list, char **envp);
void	env_expansion_string(char **string, char **envp);
char	**env_split(char *command);
void	quote_trim(t_list *list);
void	free_empty(t_list *list);
char	*assemble(t_list *dis);
char	*disassemble_assemble(char *fuck, char **envp);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_echo(char *line, t_list *node);

void	free_space(t_list *list);
void	quote_trim(t_list *list);
int	quote_check(t_list *list);
// int		command_run(t_list* list, char *line, t_copy *e);
#endif
