CC=cc
CFLAGS=-I include -pthread
NAME=philo
OBJ_DIR=obj
SRC=mutex/destroy.c mutex/init.c mutex/lock.c activity.c announce.c callback.c cleanup.c eat.c fork_available.c fork.c is_philo.c is_philo2.c malloc2.c parse.c philo.c setup.c terminate.c time.c
OBJ=$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
HEADERS=include/philodef.h include/philo.h

ifndef LENIENT
	CFLAGS += -Wall -Wextra -Werror
endif

ifdef DEBUG
	CFLAGS += -g
endif

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

norm:
	norminette $(SRC) $(HEADERS)

.PHONY:
	all bonus clean fclean test norm