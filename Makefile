# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:32:15 by luiberna          #+#    #+#              #
#    Updated: 2024/05/07 22:29:19 by luiberna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c parsing.c init.c free.c env.c

CC = cc

OBJS = $(SRCS:.c=.o)

INCLUDE = ./Includes/

CFLAGS = -I$(INCLUDE) -g #-Wall -Wextra -Werror 

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./Libft
	$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME) -lreadline

clean:
	make clean -C ./Libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./Libft
	rm -f $(NAME)

re: fclean $(NAME)

r: 
	make re && ./fdf 

.PHONY: all clean fclean re


