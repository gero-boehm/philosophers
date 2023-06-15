CC=cc
CFLAGS=-I shared/include -I philo -I philo_bonus
NAME=philo
SHARED=shared/mutex/init.c shared/mutex/lock.c shared/mutex/destroy.c shared/parse.c
SRC=$(SHARED) philo/philo.c philo/fork.c
BONUS_SRC=
OBJ=$(SRC:.c=.o)
BONUS_OBJ=$(BONUS_SRC:.c=.o)
HEADERS=philo/philo.h

ifndef LENIENT
	CFLAGS += -Wall -Wextra -Werror
endif

ifdef DEBUG
	CFLAGS += -g
endif

all: $(NAME)

%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o philo/$(NAME) $^

bonus: $(BONUS_OBJ)
	$(CC) $(CFLAGS) -o philo_bonus/philo_bonus $^

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f philo/$(NAME) philo_bonus/philo_bonus

re: fclean all

test: all
	./philo/$(NAME)

norm:
	norminette $(SRC) $(BONUS_SRC) $(HEADERS)

.PHONY:
	all bonus clean fclean test norm