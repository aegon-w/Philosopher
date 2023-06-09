NAME = philo_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = philo_bonus.c check_inp.c philo_bonus_utils.c


INCLUDES = philo_bonus.h

all: $(NAME) $(SRCSB)

$(NAME): $(INCLUDES) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean :
	rm -f $(NAME)

fclean :	clean

re : fclean all

.PHONY: re all fclean clean bonus