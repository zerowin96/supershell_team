/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:51:36 by minsulee          #+#    #+#             */
/*   Updated: 2023/01/18 16:29:35 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

// typedef struct s_list
// {
// 	char			content[BUFFER_SIZE + 1];
// 	struct s_list	*next;
// }					t_list;

char	*get_next_line(int fd);
char	*find_nl_print(int fd, char *buffer, t_list *head);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	free_all(t_list *head);
t_list	*head_initialize(void);
size_t	ft_strlen(const char *s);
char	*buffer_printer(char *buffer, size_t index, t_list *head);
void	content_copy(t_list *head, size_t str_len, char *ret_str);
char	*read_free_bufferpush_return(t_list *head, char *buffer, ssize_t index);
size_t	list_gen_with_newstr(char *str, t_list *head, size_t len);

#endif
