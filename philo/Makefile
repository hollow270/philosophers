CC = gcc -g #-Wall -Wextra -Werror

HED = inc/philo.h

INC = inc/
SRC = src/main.c \
src/ft_atoi.c \
src/gc.c \
src/initialize_philos.c \
src/cctv.c \
src/habits.c \
src/utils.c \
src/gc_mutex.c
OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -I$(INC) $(OBJ) -o $(NAME)

%.o: %.c $(HED)
	$(CC) -I$(INC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean