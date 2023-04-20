
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c89 -pedantic
INCLUDE = include

all:
	$(CC) $(CFLAGS) -I $(INCLUDE) src/jumbo_num.c tests/jumbo_num_tests.c
	./a.out
