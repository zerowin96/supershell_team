# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yeham <yeham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 10:09:55 by yeham             #+#    #+#              #
#    Updated: 2023/02/03 12:02:37 by yeham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -MMD

CMPFLAGS = libft/libft.a -lreadline -L${HOME}/.brew/opt/readline/lib
INFLAGS	= -I${HOME}/.brew/opt/readline/include 

BUILTIN_SRCS = $(addprefix builtin/, builtin_util.c cd.c echo.c env_split.c env.c exit.c export.c export2.c pwd.c unset.c)
ETC_SRCS = $(addprefix etc/, signal.c vector.c vector2.c)
EXEC_SRCS = $(addprefix exec/, run_builtin.c run_child.c run_child_checkaccess.c run_command.c run_single_builtin.c run_split.c run_split_sep.c run_util_general.c run_util_quote.c)
MAIN_SRCS = $(addprefix main/, main.c main_heredoc1.c main_heredoc2.c main_while_init.c)
PARSE_SRCS = $(addprefix parsing/, parse.c parse_env_expansion.c parse_qm_expansion.c parse_sep.c parse_tokenize.c parse_util.c)

SRCS	:= $(BUILTIN_SRCS) $(ETC_SRCS) $(EXEC_SRCS) $(MAIN_SRCS) $(PARSE_SRCS)

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

all : $(NAME)

$(NAME) : $(OBJS) libft/libft.a
	cc $(CFLAGS) $(OBJS) -o $(NAME) $(CMPFLAGS)

libft/libft.a :
	make -C libft bonus

%.o : %.c
	cc $(CFLAGS) -c $< -o $@ $(INFLAGS)

clean :
	make -C libft clean
	rm -f $(OBJS) $(DEPS)

fclean :
	make clean
	make -C libft fclean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re

-include $(DEPS)
