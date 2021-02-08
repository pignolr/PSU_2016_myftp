##
## Makefile for ftrace in /home/frejimap/Documents/Epitech/PSU/PSU_2016_ftrace
## 
## Made by Frejimap
## Login   <remi.pignol@epitech.eu>
## 
## Started on  Tue May  2 15:33:16 2017 Frejimap
## Last update Sat May 20 17:32:06 2017 Frejimap
##

CC		= gcc

CFLAGS		+= -W -Wall -Wextra -Werror -march=native -O2

CPPFLAGS	+= -Iinc

LDFLAGS		+=

NAME		= server

SRCS		= src/main.c \
		src/fd.c \
		src/server_launch.c \
		src/catch_sig.c \
		src/server_loop.c \
		src/client_main.c \
		src/command_basic.c \
		src/command_user.c \
		src/command_directory.c \
		src/command_port.c \
		src/command_passv.c \
		src/command_file.c \
		src/command_list.c


OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -f  $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
