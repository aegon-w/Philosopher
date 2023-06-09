NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = philo.c philo_utils.c check_inp.c philo_utils1.c


INCLUDES = philo.h

all: $(NAME) $(SRCSB)

$(NAME): $(INCLUDES) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean :
	rm -f $(NAME)

fclean :	clean

re : fclean all

.PHONY: re all fclean clean bonus