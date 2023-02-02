# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 10:09:55 by yeham             #+#    #+#              #
#    Updated: 2023/02/02 18:43:42 by minsulee         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

# NAME = minishell

# CFLAGS = -Wall -Wextra -Werror

# LDFLAGS	= -L$(shell brew --prefix readline)/lib
# CPPFLAGS = -I$(shell brew --prefix readline)/include

# SRCS	= test.c hello.c
# OBJS	= $(SRCS:.c=.o)

# all : $(NAME)

# $(NAME): $(OBJS)
# 	cc $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(LDFLAGS) $(CPPFLAGS)

# %.o : %.c
# 	cc $(CFLAGS) -c $< -o $@

# clean :
# 	rm -f $(OBJS)

# fclean :
# 	make clean
# 	rm -f $(NAME)

# re : 
# 	make fclean
# 	make all

# .PHONY : all clean fclean re

all :
	make -C libft bonus
#	make -C libft clean
#	make -C get_next_line all
#	make -C get_next_line clean
	gcc -g3 -lreadline -L/Users/minsulee/.brew/opt/readline/lib -I/Users/minsulee/.brew/opt/readline/include \
	libft/libft.a cd.c echo.c env_split.c env.c exit.c export.c parse.c pwd.c \
	main.c unset.c vector.c vector2.c heredoc.c signal.c export2.c split_and_merge_space.c \
	run_builtin.c run_child.c run_command.c run_single_builtin.c run_split.c main_while_init.c \
	run_child_checkaccess.c run_split_sep.c run_util_general.c run_util_quote.c \
	parse_env_expansion.c parse_qm_expansion.c parse_sep.c parse_tokenize.c parse_util.c
#	gcc -g3 -lreadline -L/Users/minsulee/.brew/opt/readline/lib -I/Users/minsulee/.brew/opt/readline/include libft/libft.a cd.c echo.c env_split.c env.c exit.c export.c minsu_test_tokenize.c pwd.c test.c unset.c vector.c heredoc.c signal.c
#	gcc -g3 -o minishell -lreadline libft/libft.a get_next_line/get_next_line.a cd.c echo.c env_split.c env.c exit.c export.c minsu_test_tokenize.c pwd.c test.c unset.c vector.c && chmod 777 minishell

clean :
	make -C libft clean
#	make -C get_next_line clean