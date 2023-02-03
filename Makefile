# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 10:09:55 by yeham             #+#    #+#              #
#    Updated: 2023/02/03 09:35:39 by minsulee         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

CMPFLAGS = libft/libft.a -lreadline -L${HOME}/.brew/opt/readline/lib
INFLAGS	= -I${HOME}/.brew/opt/readline/include 
#CPPFLAGS = -I$(shell brew --prefix readline)/include

BUILTIN_SRCS = $(addprefix builtin/, builtin_util.c cd.c echo.c env_split.c env.c exit.c export.c export2.c pwd.c unset.c)
ETC_SRCS = $(addprefix etc/, signal.c vector.c vector2.c)
EXEC_SRCS = $(addprefix exec/, run_builtin.c run_child.c run_child_checkaccess.c run_command.c run_single_builtin.c run_split.c run_split_sep.c run_util_general.c run_util_quote.c)
MAIN_SRCS = $(addprefix main/, main.c main_heredoc1.c main_heredoc2.c main_while_init.c)
PARSE_SRCS = $(addprefix parsing/, parse.c parse_env_expansion.c parse_qm_expansion.c parse_sep.c parse_tokenize.c parse_util.c)

SRCS	:= $(BUILTIN_SRCS) $(ETC_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(PARSE_SRCS)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) libft/libft.a
	cc $(CFLAGS) $(OBJS) -o $(NAME) $(CMPFLAGS)

libft/libft.a :
	make -C libft bonus

%.o : %.c
	cc $(CFLAGS) -c $< -o $@ $(INFLAGS)

clean :
	make -C libft clean
	rm -f $(OBJS)

fclean :
	make clean
	make -C libft fclean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re

#all :
#	make -C libft bonus
##	make -C libft clean
##	make -C get_next_line all
##	make -C get_next_line clean
#	gcc -g3 -lreadline -L/Users/minsulee/.brew/opt/readline/lib -I/Users/minsulee/.brew/opt/readline/include \
#	libft/libft.a cd.c echo.c env_split.c env.c exit.c export.c parse.c pwd.c \
#	main.c unset.c vector.c vector2.c heredoc.c signal.c export2.c split_and_merge_space.c \
#	run_builtin.c run_child.c run_command.c run_single_builtin.c run_split.c main_while_init.c \
#	run_child_checkaccess.c run_split_sep.c run_util_general.c run_util_quote.c \
#	parse_env_expansion.c parse_qm_expansion.c parse_sep.c parse_tokenize.c parse_util.c
##	gcc -g3 -lreadline -L/Users/minsulee/.brew/opt/readline/lib -I/Users/minsulee/.brew/opt/readline/include libft/libft.a cd.c echo.c env_split.c env.c exit.c export.c minsu_test_tokenize.c pwd.c test.c unset.c vector.c heredoc.c signal.c
##	gcc -g3 -o minishell -lreadline libft/libft.a get_next_line/get_next_line.a cd.c echo.c env_split.c env.c exit.c export.c minsu_test_tokenize.c pwd.c test.c unset.c vector.c && chmod 777 minishell
#
#clean :
#	make -C libft clean
##	make -C get_next_line clean