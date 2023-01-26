# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 10:09:55 by yeham             #+#    #+#              #
#    Updated: 2023/01/26 10:29:01 by minsulee         ###   ########seoul.kr   #
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
	gcc -g3 -lreadline libft/libft.a get_next_line/get_next_line.a cd.c echo.c env_split.c env.c exit.c export.c minsu_test_tokenize.c pwd.c test.c unset.c vector.c