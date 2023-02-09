/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:45:46 by minsulee          #+#    #+#             */
/*   Updated: 2023/02/09 13:59:59 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
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
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define READ 0
# define WRITE 1
# define PREV 0
# define NEXT 1

// typedef struct s_cnt
// {
// 	char	**order;
// 	int		pipe_cnt;
// 	int		q_flag;
// }	t_cnt;
typedef struct s_copy
{
	char	**cp_envp;
	char	**onlyenv;
}	t_copy;

t_list		*first_parsing(char **line);
t_list		*parsing(char *line);
void		ft_unset(char **command, t_copy *env);
void		ft_env(t_copy *e);
int			ft_export(char **command, t_copy *env);
char		**vector_add(char **vector, char *string);
void		vector_replace(char **vector, \
				int replace_index, char *replace_string);
void		vector_replace2(char **vector, \
				int replace_index, char *replace_string);
char		**vector_delete_index(char **vector, int delete_index);
void		vector_free(char **vector);
int			string_compare(char *string, char *compare);
int			get_vector_len(char **vector);
void		env_expansion(t_list *list, char **envp);
// void		env_expansion_string(t_list **list, char **envp)
// void		env_expansion_string(char **string, char **envp);
void		env_expansion_string(t_list **list, char **envp);
// void	env_expansion_string(t_list *cursor, char **envp);
char		**env_split(char *command);
void		free_empty(t_list *list);
char		*assemble(t_list *dis);
char		*disassemble_assemble(char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_echo(char **command);
void		ft_pwd(void);
int			ft_cd(char *next, t_copy *env);
int			is_separator(char *string);
void		handle_signal(void);
void		blank_list_module(char **string, t_list *new);
void		parent_handle_signal(void);
void		heredoc_handle_signal(void);
void		child_handle_signal(void);
void		sort_and_print(char **string);
void		free_space(t_list *list);
int			quote_check(t_list *list);
void		free_list(t_list *list);
int			heredoc(t_list *list);
int			delete_local_file(t_list *list);
int			command_split(t_list *temp, int (*fd)[2], \
				char ***command, char **string);
int			main_builtin(t_list **list, int *result, t_copy *env);
int			builtin_exec(char **command, t_copy *e);
void		child_process(t_list **list, t_copy *e, int fd[2][2], int result);
int			command_run(t_list *list, t_copy *e, int result);
int			main_while_init(t_list **list, char **line, int *result);
char		*string_connect(char *dst, char *src);
int			command_split_separator(t_list **temp, int (*fd)[2], int sep);
int			pipe_exists(t_list *line);
int			builtin_check(char *string);
int			check_access(char *name, char **paths, int permission);
int			sep_kind(t_list *node);
void		tokenize(t_list *list, char *string);
void		tokenize_2(t_list *list, char *string);
char		*ft_strjoin2(const char *rep, \
				const char *src, int start, int finish);
void		quote_trim(t_list *list);
void		qmark_expansion(t_list *list, int pres);
char		*get_filename(void);
int			export_error_check(char *string);
void		child_command_error(char *command, int errcheck);

// void		list_print(char *string, t_list *list);
t_list		*vector_to_list(char ***vector);
char		**list_to_vector(t_list *list);
int			ml_iswhite(char c);
// char		**whitespace_split(char *string);
// void		list_whitespace_split(t_list *list);
void		list_tie(t_list *temp);

// void		list_tie_2(t_list *temp);
void		ft_exit(char *command, char *next_command);
void		parse_expand(char ***command, int result, t_copy *env);

void		tokenize_space(t_list *list, char *string, int *index);
void		tokenize_separator(t_list *list, char *string, int *index);
void		tokenize_string(t_list *list, char *string, int *index);
void		tokenize_expansion(t_list *list, char *string, int *index);
void		partial_string(t_list *list, char *string, int start, int finish);
void		vector_print(char *string, char **vector);
void		list_print(char *string, t_list *list);
char		**env_expansion_string_vector(char *string);
void		env_expansion_v2elst(t_list **temp_expand, \
				char ***vector, char **envp);
#endif
