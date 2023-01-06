# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 16:44:40 by minsulee          #+#    #+#              #
#    Updated: 2023/01/05 14:51:19 by minsulee         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra
AR		:= ar
ARFLAGS := -rcs
NAME := pipex
LIBFT_A := ../libft/libft.a

# SRCS := pipex.c \
# pipex_parent.c \
# pipex_junction.c \
# pipex_gnl.c \
# pipex_child.c

# SRCS_H := pipex.h
# OBJS	:= $(SRCS:.c=.o)

SRCS := bpipex_bonus.c \
bpipex_parent_bonus.c \
bpipex_junction_bonus.c \
bpipex_here_doc_bonus.c \
bpipex_gnl_bonus.c \
bpipex_child_bonus.c

# SRCS_BONUS_H := bpipex_bonus.h
# OBJS_BONUS :=	$(SRCS_BONUS:.c=.o)

SRCS_H := bpipex_bonus.h
OBJS :=	$(SRCS_BONUS:.c=.o)

# ifdef WITH_BONUS
# OBJECTS = $(OBJS_BONUS)
# HEADER := $(SRCS_BONUS_H)
# else
# OBJECTS = $(OBJS)
# HEADER := $(SRCS_H)
# endif

all : $(NAME)

$(NAME) : $(OBJECTS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_A) -o $@

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBFT_A) :
	make -C ../libft all

clean :
	rm -rf $(OBJS) $(OBJS_BONUS)
	make -C ../libft clean

fclean : clean
	rm -rf $(NAME)
	make -C ../libft fclean

re :
	make fclean
	make all

# bonus :
# 	make WITH_BONUS=1 all


.PHONY : clean re fclean all
